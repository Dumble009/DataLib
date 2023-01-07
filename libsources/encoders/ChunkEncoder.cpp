#include "ChunkEncoder.h"
#include <fstream>

namespace data
{
    namespace encoder
    {
        ChunkEncoder::ChunkEncoder()
        {
            writeData = std::vector<char>();
        }

        DataLibErrorCode ChunkEncoder::Write(const std::string &path)
        {
            std::ofstream fout;
            fout.open(path, std::ios::out | std::ios::binary | std::ios::trunc);

            // ファイルオープンに失敗した場合
            if (!fout)
            {
                return DataLibErrorCode::DATA_LIB_OPEN_FILE_FAILED;
            }

            fout.write(writeData.begin()._Ptr, sizeof(char) * writeData.size());

            return DataLibErrorCode::DATA_LIB_SUCCESS;
        }
    }
}