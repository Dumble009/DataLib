#include <gtest/gtest.h>

#include "decoders/Decoder.h"
#include "../TestStruct.h"

#define MAKE_VECTOR(type, vecName, ...) \
    type array[] = {__VA_ARGS__};       \
    std::vector<type> vecName(array, std::end(array))

std::string GetPath(const std::string &fileName)
{
    std::string p = "test_datas/decoder_datas/";
    p += fileName;

    return p;
}

template <class T>
void CheckVector(const std::vector<T> &real, const std::vector<T> &ans)
{
    ASSERT_EQ(real.size(), ans.size());
    auto s = real.size();
    for (int i = 0; i < s; i++)
    {
        ASSERT_EQ(real[i], ans[i]);
    }
}

TEST(DecodeBoolTest, BasicAssertions)
{
    auto decoder = data::decoder::Decoder();
    bool b = false;

    const std::string path = GetPath("testInputBool");
    auto ret = decoder.Decode(&b, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);
    ASSERT_EQ(b, true);
}

TEST(DecodeIntTest, BasicAssertions)
{
    auto decoder = data::decoder::Decoder();
    int i = 0;

    const std::string path = GetPath("testInputInt");
    auto ret = decoder.Decode(&i, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);
    ASSERT_EQ(i, 0x89ABCDEF);
}

TEST(DecodeDoubleTest, BasicAssertions)
{
    auto decoder = data::decoder::Decoder();

    double d = 0.0;

    const std::string path = GetPath("testInputDouble");
    auto ret = decoder.Decode(&d, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);
    ASSERT_EQ(d, 64.0);
}

TEST(DecodeVectorIntTest, BasicAssertions)
{
    auto decoder = data::decoder::Decoder();

    std::vector<int> iv{};

    const std::string path = GetPath("testInputVecInt");
    auto ret = decoder.Decode(&iv, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);

    MAKE_VECTOR(int, ans, 0x01234567, 0x89ABCDEF, 0x00000000);
    CheckVector(iv, ans);
}

TEST(DecodeVectorDoubleTest, BasicAssertions)
{
    auto decoder = data::decoder::Decoder();

    std::vector<double> dv{};

    const std::string path = GetPath("testInputVecDouble");
    auto ret = decoder.Decode(&dv, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);

    MAKE_VECTOR(double, ans, 128.0);
    CheckVector(dv, ans);
}

TEST(DecodeStructTest, BasicAssertions)
{
    auto decoder = data::decoder::Decoder();

    auto stru = TestStruct();

    const std::string path = GetPath("testInputStruct");
    auto ret = decoder.Decode(&stru, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);

    auto ans = TestStruct();
    ans.b = true;
    ans.i = 0x89ABCDEF;
    ans.d = 32.0;

    ASSERT_EQ(stru, ans);
}

TEST(DecodeVecStructTest, BasicAssertions)
{
    auto decoder = data::decoder::Decoder();

    std::vector<TestStruct> sv{};
    const std::string path = GetPath("testInputVecStruct");
    auto ret = decoder.Decode(&sv, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);

    TestStruct stru1 = {
        true,
        0x89ABCDEF,
        32.0};
    TestStruct stru2 = {
        false,
        0xFEDCBA98,
        0.0};

    MAKE_VECTOR(TestStruct, ans, stru1, stru2);
    ASSERT_EQ(sv, ans);
}