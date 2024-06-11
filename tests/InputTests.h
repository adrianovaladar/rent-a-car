#ifndef INPUTTESTS_H
#define INPUTTESTS_H
#include <gtest/gtest.h>

class InputTests : public ::testing::Test {
protected:
    FILE* file{};
    int value{};
};


#endif //INPUTTESTS_H
