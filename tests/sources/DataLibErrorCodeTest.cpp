#include <gtest/gtest.h>

#include <string>
#include <sstream>

#include "DataLibErrorCode.h"

void CheckErrorCodeString(data::DataLibErrorCode code,
                          const std::string &ans)
{
    std::string result = data::ConvertDataLibErrorCodeToString(code);
    ASSERT_EQ(result, ans);

    std::stringstream sstr;
    sstr << code;
    ASSERT_EQ(sstr.str(), ans);
}

// DataLibErrorCodeを文字列に変換した結果やストリームへの挿入が正しいかどうかチェックする
TEST(ErrorCodeToStringTest, BasicAssertions)
{
    CheckErrorCodeString(data::DataLibErrorCode::DATA_LIB_SUCCESS,
                         "DATA_LIB_SUCCESS");
    CheckErrorCodeString(data::DataLibErrorCode::DATA_LIB_FAILED_TO_ENCODE,
                         "DATA_LIB_FAILED_TO_ENCODE");
    CheckErrorCodeString(data::DataLibErrorCode::DATA_LIB_FAILED_TO_DECODE,
                         "DATA_LIB_FAILED_TO_DECODE");
    CheckErrorCodeString(data::DataLibErrorCode::DATA_LIB_FAILED_TO_DECODE_VECTOR,
                         "DATA_LIB_FAILED_TO_DECODE_VECTOR");
    CheckErrorCodeString(data::DataLibErrorCode::DATA_LIB_FAILED_TO_OPEN_FILE,
                         "DATA_LIB_FAILED_TO_OPEN_FILE");
    CheckErrorCodeString(data::DataLibErrorCode::DATA_LIB_FAILED_TO_WRITE_DATA,
                         "DATA_LIB_FAILED_TO_WRITE_DATA");
    CheckErrorCodeString(data::DataLibErrorCode::DATA_LIB_FAILED_TO_READ_DATA,
                         "DATA_LIB_FAILED_TO_READ_DATA");
}