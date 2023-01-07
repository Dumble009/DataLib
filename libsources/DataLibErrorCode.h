#pragma once

namespace data
{
    // DataLibに関する関数を実行した結果のエラーコード
    enum class DataLibErrorCode
    {
        DATA_LIB_SUCCESS = 0,
        DATA_LIB_OPEN_FILE_FAILED = 1,
    };
}