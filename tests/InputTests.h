#ifndef APPLICATIONTESTS_H
#define APPLICATIONTESTS_H
#include <gtest/gtest.h>

class InputTests : public ::testing::Test {
protected:
    FILE* file{};
    int value{};
};


#endif //APPLICATIONTESTS_H
