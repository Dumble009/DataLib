#pragma once
#include <vector>
#include <string>

#include "../DataLibErrorCode.h"

namespace data
{
    namespace decoder
    {
        class Decoder
        {
        private:
            std::vector<char> readBytes; // ファイルから読み込んだバイト配列

            template <class T>
            DataLibErrorCode DecodeImp(T *data,
                                       const std::vector<char> &bytes,
                                       int *head,
                                       int option,
                                       int metadata);

            template <class T>
            DataLibErrorCode DecodeImp(std::vector<T> *data,
                                       const std::vector<char> &bytes,
                                       int *head,
                                       int option,
                                       int metadata);

        public:
            Decoder();

            DataLibErrorCode Read(const std::string &path);

            template <class T>
            DataLibErrorCode Decode(T *data,
                                    const std::string &path,
                                    int option);
        };

        template <class T>
        DataLibErrorCode Decoder::DecodeImp(T *data,
                                            const std::vector<char> &bytes,
                                            int *head,
                                            int option,
                                            int metadata)
        {
            try
            {
                size_t size = sizeof(T);

                // dataのポインタをcharのポインタに変換
                // VC++のreinterpret_castにはバグがある？ようで上手く動かないので使わない
                auto bytePtr = (char *)(void *)data;

                for (int i = 0; i < size; i++)
                {
                    bytePtr[i] = bytes[*head + i];
                }

                *head += (int)size;

                return DataLibErrorCode::DATA_LIB_SUCCESS;
            }
            catch (...)
            {
                return DataLibErrorCode::DATA_LIB_FAILED_TO_DECODE;
            }
        }

        template <class T>
        DataLibErrorCode Decoder::DecodeImp(std::vector<T> *data,
                                            const std::vector<char> &bytes,
                                            int *head,
                                            int option,
                                            int metadata)
        {
            try
            {
                // まずはベクタのサイズを取り出す。
                size_t dataSize = 0;
                auto ret = DecodeImp(&dataSize, bytes, head, option, metadata);
                if (!IsDataLibActionSucceeded(ret))
                {
                    return ret;
                }

                // 取得したデータ数の領域を確保し、そこに順番に値を入れていく
                data->resize(dataSize);
                for (auto itr = data->begin(); itr != data->end(); itr++)
                {
                    ret = DecodeImp(itr._Ptr, bytes, head, option, metadata);
                    if (!IsDataLibActionSucceeded(ret))
                    {
                        return ret;
                    }
                }

                return DataLibErrorCode::DATA_LIB_SUCCESS;
            }
            catch (...)
            {
                return DataLibErrorCode::DATA_LIB_FAILED_TO_DECODE_VECTOR;
            }
        }

        template <class T>
        DataLibErrorCode Decoder::Decode(T *data,
                                         const std::string &path,
                                         int option)
        {
            // まずはpathが示すファイルからreadBytesにバイト列を読み込む
            auto ret = Read(path);
            if (!IsDataLibActionSucceeded(ret))
            {
                return ret;
            }

            int head = 0;

            // まずはファイル先頭に入れられているメタデータを読む。
            // この段階ではメタデータは存在していないので、DecodeImpのmetadata引数には0(デフォルト)を渡しておく
            int metadata = 0;
            ret = DecodeImp(&metadata, readBytes, &head, option, 0);

            ret = DecodeImp(data, readBytes, &head, option, metadata);
            if (!IsDataLibActionSucceeded(ret))
            {
                return ret;
            }

            return DataLibErrorCode::DATA_LIB_SUCCESS;
        }
    }
}