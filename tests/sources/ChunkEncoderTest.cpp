#include <gtest/gtest.h>
#include <fstream>
#include "DataStructure.h"
#include "encoders/ChunkEncoder.h"

#define TEST_OUTPUT1 "outputs/TestOutput1"

// buffer内のheadから始まる4バイトとv1,v2,v3,v4をそれぞれ比較する
void CompareBuffer4byte(const char *buffer, int head, char v1, char v2, char v3, char v4)
{
    ASSERT_EQ(buffer[head], v1);
    ASSERT_EQ(buffer[head + 1], v2);
    ASSERT_EQ(buffer[head + 2], v3);
    ASSERT_EQ(buffer[head + 3], v4);
}

TEST(ChunkEncoderTestInt, BasicAssertions)
{
    auto encoder = data::encoder::ChunkEncoder();
    int array[] = {0, 1, 2, 3}; // 16バイト
    auto ret = encoder.Encode(array,
                              4,
                              TEST_OUTPUT1,
                              data::DATA_STRUCTURE_NO_COMPRESS);

    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);

    constexpr int buf_size = 128;
    char buffer[buf_size]{0x00};

    std::ifstream ifs(TEST_OUTPUT1);
    ASSERT_FALSE(ifs.fail());

    int idx = 0;
    while (ifs.get(buffer[idx]))
    {
        idx++;
    }

    ASSERT_EQ(idx, 16); // 16バイト読み込み切ったら、次に書き込むインデックスは16番

    CompareBuffer4byte(buffer, 0, 0x00, 0x00, 0x00, 0x00);
    CompareBuffer4byte(buffer, 4, 0x00, 0x00, 0x00, 0x01);
    CompareBuffer4byte(buffer, 8, 0x00, 0x00, 0x00, 0x02);
    CompareBuffer4byte(buffer, 12, 0x00, 0x00, 0x00, 0x03);
}