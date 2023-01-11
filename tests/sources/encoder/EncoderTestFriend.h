#pragma once
#include <gtest/gtest.h>
#include "encoders/Encoder.h"

#define TESTING

class EncoderTestFriend
{
public:
    void TestT(data::encoder::Encoder &encoder);
};