#include <gtest/gtest.h>
#include "Encoders/Encoder.h"

TEST(EncodeTTest, BasicAssertions)
{
    auto encoder = data::encoder::Encoder();

    int intData = 0x89ABCDEF;

    const std::string path = "test_datas/testOutput1";

    auto ret = encoder.Encode(intData, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);
}