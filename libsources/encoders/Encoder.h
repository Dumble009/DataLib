#pragma once
#include <vector>
#include <string>
#include "../DataLibErrorCode.h"

namespace data
{
    namespace encoder
    {
        class Encoder
        {
        private:
            std::vector<char> internalBytes; // エンコードしたデータを保存しておくための配列

            // vectorのエンコーダ
            template <class T>
            DataLibErrorCode EncodeImp(const std::vector<T> &data,
                                       std::vector<char> &bytes,
                                       int option);

            // 任意の型のエンコーダ
            template <class T>
            DataLibErrorCode EncodeImp(const T &data,
                                       std::vector<char> &bytes,
                                       int option);

            // internalBytesをファイルに出力する
            DataLibErrorCode Write(const std::string &path);

        public:
            Encoder();

            template <class T>
            DataLibErrorCode Encode(const T &data,
                                    const std::string &path,
                                    int option);

#ifdef TESTING
        public:
            friend class EncoderTestFriend;
#endif
        };

        template <class T>
        DataLibErrorCode Encoder::EncodeImp(const std::vector<T> &data,
                                            std::vector<char> &bytes,
                                            int option)
        {
            // コンテナクラスをエンコードする時は、まず要素数を書き込む
            auto size = data.size();
            EncodeImp(size, bytes, option);

            // 要素数を書き込んだ後、各要素を順番に書き込んでいく
            for (const auto &elem : data)
            {
                auto ret = EncodeImp(elem, bytes, option);

                // 途中でエンコードに失敗した場合はその時点でリターン
                if (ret != DataLibErrorCode::DATA_LIB_SUCCESS)
                {
                    return ret;
                }
            }

            return DataLibErrorCode::DATA_LIB_SUCCESS;
        }

        template <class T>
        DataLibErrorCode Encoder::EncodeImp(const T &data,
                                            std::vector<char> &bytes,
                                            int option)
        {
            try
            {
                auto sizeT = sizeof(T);

                // dataのポインタをcharのポインタに読み替え
                // reinterpret_castはVC++ではバグがあるらしい？上手く行かない時がある
                auto bytePtr = (char *)(void *)(&data);

                for (size_t i = 0; i < sizeT; i++)
                {
                    bytes.push_back(bytePtr[i]);
                }

                return DataLibErrorCode::DATA_LIB_SUCCESS;
            }
            catch (...)
            {
                // 何らかの例外が発生した場合はエラーコードを投げる。
                // 例外の内容によって細分化した方がいいかも
                return DataLibErrorCode::DATA_LIB_FAILED_TO_ENCODE;
            }
        }

        template <class T>
        DataLibErrorCode Encoder::Encode(const T &data,
                                         const std::string &path,
                                         int option)
        {
            auto ret = EncodeImp(data, internalBytes, option);
            if (ret != DataLibErrorCode::DATA_LIB_SUCCESS)
            {
                return ret;
            }

            // エンコードが完了したら得られたバイト列をファイルに書き込む
            ret = Write(path);
            if (ret != DataLibErrorCode::DATA_LIB_SUCCESS)
            {
                return ret;
            }

            return DataLibErrorCode::DATA_LIB_SUCCESS;
        }
    }
}