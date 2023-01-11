#include <gtest/gtest.h>
#include "Encoders/Encoder.h"

#include <fstream>

// バイト配列bufferのheadから4バイトとb1,b2,b3,b4を比較する
void Compare4Bytes(const char *buffer, int head, char b1, char b2, char b3, char b4)
{
    ASSERT_EQ(buffer[head], b1);
    ASSERT_EQ(buffer[head + 1], b2);
    ASSERT_EQ(buffer[head + 2], b3);
    ASSERT_EQ(buffer[head + 3], b4);
}

TEST(EncodeTTest, BasicAssertions)
{
    auto encoder = data::encoder::Encoder();

    int intData = 0x89ABCDEF;

    const std::string path = "test_datas/testOutput1";

    auto ret = encoder.Encode(intData, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);

    std::ifstream ifs(path);
    ASSERT_FALSE(ifs.fail());

    // bufferの末尾にifsから呼んだ値を入れていく
    std::vector<char> buffer{};
    int idx = 0; // 次にbufferの何番目に値を格納するか
    buffer.push_back(0);
    while (ifs.get(buffer.back()))
    {
        idx++;
        buffer.push_back(0);
    }

    ASSERT_EQ(idx, 4); // int型は4バイトなので、idx==4のはず
    Compare4Bytes(buffer.begin()._Ptr, 0, 0xEF, 0xCD, 0xAB, 0x89);
}