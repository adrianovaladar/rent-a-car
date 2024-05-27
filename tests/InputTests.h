#ifndef APPLICATIONTESTS_H
#define APPLICATIONTESTS_H
#include <gtest/gtest.h>

class InputTests : public ::testing::Test {
protected:
    FILE* file{};
    int option{};
};


#endif //APPLICATIONTESTS_H
