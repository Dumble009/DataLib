#pragma once

#include <string>
#include <iostream>

namespace data
{

    enum class DataLibErrorCode : int
    {
        DATA_LIB_SUCCESS = 0,
        DATA_LIB_FAILED_TO_ENCODE = 1,
        DATA_LIB_FAILED_TO_DECODE = 2,
        DATA_LIB_FAILED_TO_DECODE_VECTOR = 3,
        DATA_LIB_FAILED_TO_OPEN_FILE = 4,
        DATA_LIB_FAILED_TO_WRITE_DATA = 5,
        DATA_LIB_FAILED_TO_READ_DATA = 6,
    };

    std::ostream &operator<<(std::ostream &os, DataLibErrorCode code);

    std::string ConvertDataLibErrorCodeToString(DataLibErrorCode code);

    // DataLibErrorCodeを返す関数の結果を受け取り、正常に終了したかどうか判定する
    inline bool IsDataLibActionSucceeded(DataLibErrorCode code)
    {
        // inline関数なのでヘッダに記述する必要がある
        return code == DataLibErrorCode::DATA_LIB_SUCCESS;
    }
}