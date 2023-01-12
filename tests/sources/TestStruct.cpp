#include "TestStruct.h"

bool TestStruct::operator==(const TestStruct &t) const
{
    return this->b == t.b && this->i == t.i && this->d == t.d;
}

bool TestStruct::operator!=(const TestStruct &t) const
{
    return !(*this == t);
}