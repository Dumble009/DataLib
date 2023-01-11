#include <gtest/gtest.h>
#include "Encoders/Encoder.h"

#include <fstream>

void CheckEncodeResult(const std::string &path, const std::vector<char> &ans)
{
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

    ASSERT_EQ(idx, ans.size()); // idxは最終的に読み込んだバイト数になるので、ansのsizeと一致するはず

    for (int i = 0; i < idx; i++)
    {
        ASSERT_EQ(buffer[i], ans[i]);
    }
}

TEST(EncodeIntTest, BasicAssertions)
{
    auto encoder = data::encoder::Encoder();

    int intData = 0x89ABCDEF;

    const std::string path = "test_datas/testOutput1";

    auto ret = encoder.Encode(intData, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);

    char ansData[] = {0xEF, 0xCD, 0xAB, 0x89};
    std::vector<char> ans(ansData, std::end(ansData));
    CheckEncodeResult(path, ans);
}

TEST(EncodeDoubleTest, BasicAssertions)
{
    auto encoder = data::encoder::Encoder();

    double doubleData = 64.0; // 0x40500000 00000000

    const std::string path = "test_datas/testOutput2";

    auto ret = encoder.Encode(doubleData, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);

    char ansData[] = {0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x50, 0x40};
    std::vector<char> ans(ansData, std::end(ansData));
    CheckEncodeResult(path, ans);
}

TEST(EncodeVectorIntTest, BasicAssertions)
{
    auto encoder = data::encoder::Encoder();

    int intDatas[] = {0x01234567, 0x89ABCDEF, 0x00000000};
    std::vector<int> intVec(intDatas, std::end(intDatas));

    const std::string path = "test_datas/testOutput3";

    auto ret = encoder.Encode(intVec, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);

    char ansData[] = {0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 要素数3が先頭に入るsize_t=long longなので64bit
                      0x67, 0x45, 0x23, 0x01,
                      0xEF, 0xCD, 0xAB, 0x89,
                      0x00, 0x00, 0x00, 0x00};
    std::vector<char> ans(ansData, std::end(ansData));
    CheckEncodeResult(path, ans);
}

TEST(EncodeVectorDoubleTest, BasicAssertions)
{
    auto encoder = data::encoder::Encoder();

    double doubleDatas[] = {64.0};
    std::vector<double> doubleVec(doubleDatas, std::end(doubleDatas));

    const std::string path = "test_datas/testOutput4";

    auto ret = encoder.Encode(doubleVec, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);

    char ansData[] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 要素数1が先頭に入るsize_t=long longなので64bit
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x40};
    std::vector<char> ans(ansData, std::end(ansData));
    CheckEncodeResult(path, ans);
}