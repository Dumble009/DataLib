#include "Decoder.h"

#include <fstream>

namespace data
{
    namespace decoder
    {
        Decoder::Decoder() : readBytes(){};

        DataLibErrorCode Decoder::Read(const std::string &path)
        {
            // ファイルサイズを取得するために、読み取り位置を末尾にする
            std::ifstream ifs(path, std::ios::in | std::ios::binary | std::ios::ate);

            // ファイルのオープンに失敗したらエラーを返す
            if (!ifs)
            {
                return DataLibErrorCode::DATA_LIB_FAILED_TO_OPEN_FILE;
            }

            try
            {
                // ファイルを開く際に読み取り位置を末尾にしているので、
                // 現在の読み取り位置=ファイルサイズになっている
                size_t byteCounts = static_cast<size_t>(ifs.tellg());

                ifs.seekg(0, std::ifstream::beg); // 読み取り位置を先頭に移動

                readBytes.resize(byteCounts);
                ifs.read(readBytes.begin()._Ptr, byteCounts);
            }
            catch (...)
            {
                return DataLibErrorCode::DATA_LIB_FAILED_TO_READ_DATA;
            }

            return DataLibErrorCode::DATA_LIB_SUCCESS;
        }
    }
}