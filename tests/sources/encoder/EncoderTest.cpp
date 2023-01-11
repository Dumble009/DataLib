#include <gtest/gtest.h>
#include "EncoderTestFriend.h"

TEST(EncodeImpTest, BasicAssertions)
{
    auto testFriend = EncoderTestFriend();
    auto encoder = data::encoder::Encoder();

    testFriend.TestT(encoder);
}