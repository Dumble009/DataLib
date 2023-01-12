#include <gtest/gtest.h>
#include "Encoders/Encoder.h"

#include <fstream>

// path内のバイト列とansが一致するかを判定する。ansに0xFFが含まれている場合、そこはどんな値が来てもいいものとして判定をスキップする。
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
        // 0xFFはパディングなどで、どんな値が入っていても考慮しないことを意味する
        if (ans[i] == (char)0xFF)
        {
            continue;
        }
        ASSERT_EQ(buffer[i], ans[i]) << "i = " << i << std::endl;
    }
}

TEST(EncodeBoolTest, BasicAssertions)
{
    auto encoder = data::encoder::Encoder();

    bool boolData = true;

    const std::string path = "test_datas/testOutputBool";

    auto ret = encoder.Encode(boolData, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);

    char ansData[] = {0x00, 0x00, 0x00, 0x00, // メタデータ
                      0x01};
    std::vector<char> ans(ansData, std::end(ansData));
    CheckEncodeResult(path, ans);
}

TEST(EncodeIntTest, BasicAssertions)
{
    auto encoder = data::encoder::Encoder();

    int intData = 0x89ABCDEF;

    const std::string path = "test_datas/testOutputInt";

    auto ret = encoder.Encode(intData, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);

    char ansData[] = {0x00, 0x00, 0x00, 0x00, // メタデータ
                      0xEF, 0xCD, 0xAB, 0x89};
    std::vector<char> ans(ansData, std::end(ansData));
    CheckEncodeResult(path, ans);
}

TEST(EncodeDoubleTest, BasicAssertions)
{
    auto encoder = data::encoder::Encoder();

    double doubleData = 64.0; // 0x40500000 00000000

    const std::string path = "test_datas/testOutputDouble";

    auto ret = encoder.Encode(doubleData, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);

    char ansData[] = {0x00, 0x00, 0x00, 0x00, // メタデータ
                      0x00, 0x00, 0x00, 0x00,
                      0x00, 0x00, 0x50, 0x40};
    std::vector<char> ans(ansData, std::end(ansData));
    CheckEncodeResult(path, ans);
}

TEST(EncodeVectorIntTest, BasicAssertions)
{
    auto encoder = data::encoder::Encoder();

    int intDatas[] = {0x01234567, 0x89ABCDEF, 0x00000000};
    std::vector<int> intVec(intDatas, std::end(intDatas));

    const std::string path = "test_datas/testOutputVecInt";

    auto ret = encoder.Encode(intVec, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);

    char ansData[] = {0x00, 0x00, 0x00, 0x00,                         // メタデータ
                      0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 要素数3が先頭に入るsize_t=long longなので64bit
                      0x67, 0x45, 0x23, 0x01,
                      0xEF, 0xCD, 0xAB, 0x89,
                      0x00, 0x00, 0x00, 0x00};
    std::vector<char> ans(ansData, std::end(ansData));
    CheckEncodeResult(path, ans);
}

TEST(EncodeVectorDoubleTest, BasicAssertions)
{
    auto encoder = data::encoder::Encoder();

    double doubleDatas[] = {128.0}; // 0x40600000 00000000
    std::vector<double> doubleVec(doubleDatas, std::end(doubleDatas));

    const std::string path = "test_datas/testOutputVecDouble";

    auto ret = encoder.Encode(doubleVec, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);

    char ansData[] = {0x00, 0x00, 0x00, 0x00,                         // メタデータ
                      0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 要素数1が先頭に入るsize_t=long longなので64bit
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x40};
    std::vector<char> ans(ansData, std::end(ansData));
    CheckEncodeResult(path, ans);
}

struct TestStruct
{
    bool b;
    int i;
    double d;
};

TEST(EncodeStructTest, BasicAssertions)
{
    auto encoder = data::encoder::Encoder();

    auto stru = TestStruct();
    stru.b = true;
    stru.i = 0x89ABCDEF;
    stru.d = 32.0; // 0x40400000 00000000

    const std::string path = "test_datas/testOutputStruct";

    auto ret = encoder.Encode(stru, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);

    char ansData[] = {0x00, 0x00, 0x00, 0x00, // メタデータ
                      0x01,                   // true
                      0xFF, 0xFF, 0xFF,       // intは4バイトなので、4の倍数になるようにパディングが入る
                      0xEF, 0xCD, 0xAB, 0x89, // 0x89ABCDEF
                      // doubleは8バイトで、ちょうど8バイト目なのでパディングは入らない
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40};
    std::vector<char> ans(ansData, std::end(ansData));
    CheckEncodeResult(path, ans);
}

TEST(EncodeVecStructTest, BasicAssertions)
{
    auto encoder = data::encoder::Encoder();

    TestStruct struDatas[] = {
        {true, 0x89ABCDEF, 32.0},
        {false, 0xFEDCBA98, 0.0},
    };

    std::vector<TestStruct> struVec(struDatas, std::end(struDatas));

    const std::string path = "test_datas/testOutputVecStruct";

    auto ret = encoder.Encode(struVec, path, 0);
    ASSERT_EQ(ret, data::DataLibErrorCode::DATA_LIB_SUCCESS);

    char ansData[] = {0x00, 0x00, 0x00, 0x00,                         // メタデータ
                      0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 要素数2。size_tなので64ビット
                      0x01,                                           // true
                      0xFF, 0xFF, 0xFF,                               // intは4バイトなので、4の倍数になるようにパディングが入る
                      0xEF, 0xCD, 0xAB, 0x89,                         // 0x89ABCDEF
                      // doubleは8バイトで、ちょうど8バイト目なのでパディングは入らない
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40,
                      0x00,                                            // false
                      0xFF, 0xFF, 0xFF,                                // パディング
                      0x98, 0xBA, 0xDC, 0xFE,                          // 0xFEDCBA98
                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // 0.0
    std::vector<char> ans(ansData, std::end(ansData));
    CheckEncodeResult(path, ans);
}