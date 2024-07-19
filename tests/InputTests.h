#ifndef INPUTTESTS_H
#define INPUTTESTS_H
#include <gtest/gtest.h>

class InputTests : public ::testing::Test {
protected:
    FILE* inputFile{};
    FILE* outputFile{};
    int value{};
    void SetUp() override {
        inputFile = tmpfile();
#ifdef _WIN32
        outputFile = fopen("NUL", "w");
#else
        outputFile = fopen("/dev/null", "w");
#endif
    }
    void TearDown() override {
        fclose(inputFile);
        fclose(outputFile);
    }
};


#endif //INPUTTESTS_H
