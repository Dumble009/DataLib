#include "DataLibErrorCode.h"

#include <string_view>

namespace data
{
    // DataLibErrorCodeの値の番地にそれと対応する文字列を入れる
    constexpr std::string_view ERROR_CODE_STRINGS[] = {
        "DATA_LIB_SUCCESS",
        "DATA_LIB_FAILED_TO_ENCODE",
        "DATA_LIB_FAILED_TO_DECODE",
        "DATA_LIB_FAILED_TO_DECODE_VECTOR",
        "DATA_LIB_FAILED_TO_OPEN_FILE",
        "DATA_LIB_FAILED_TO_WRITE_DATA",
        "DATA_LIB_FAILED_TO_READ_DATA",
    };

    std::string ConvertDataLibErrorCodeToString(DataLibErrorCode code)
    {
        return std::string(ERROR_CODE_STRINGS[(int)code]);
    }
}