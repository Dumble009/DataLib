#include "Encoder.h"

#include <fstream>

namespace data
{
    namespace encoder
    {
        Encoder::Encoder() : internalBytes() {}

        DataLibErrorCode Encoder::Write(const std::string &path)
        {
            // バイナリ形式で上書きするように出力用のストリームを作成
            std::ofstream ofs(path, std::ios::out | std::ios::binary | std::ios::trunc);

            // ファイルのオープンに失敗したらエラーを返す
            if (!ofs)
            {
                return DataLibErrorCode::DATA_LIB_FAILED_TO_OPEN_FILE;
            }

            try
            {
                ofs.write(internalBytes.begin()._Ptr, sizeof(char) * internalBytes.size());
            }
            catch (...)
            {
                return DataLibErrorCode::DATA_LIB_FAILED_TO_WRITE_DATA;
            }
            return DataLibErrorCode::DATA_LIB_SUCCESS;
        }
    }
}