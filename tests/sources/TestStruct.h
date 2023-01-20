#pragma once

struct TestStruct
{
    bool b;
    int i;
    double d;

    bool operator==(const TestStruct &t) const;
    bool operator!=(const TestStruct &t) const;
};