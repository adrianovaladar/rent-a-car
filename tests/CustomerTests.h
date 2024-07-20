#ifndef CUSTOMERTESTS_H
#define CUSTOMERTESTS_H

#include <gtest/gtest.h>
extern "C" {
#include "../src/customer.h"
#include "../src/constants.h"
}

class CustomerTests : public ::testing::Test {
protected:
    std::array<customer, MAX_CUSTOMERS> customers {};
    std::string fileName {"test_file"};
    FILE* inputFile{};
    FILE* outputFile{};
    void SetUp() override {
        for(int i {}; i < MAX_CUSTOMERS; i++) {
            customers[i].code = i;
        }
        inputFile = tmpfile();
#ifdef _WIN32
        outputFile = fopen("NUL", "w");
#else
        outputFile = fopen("/dev/null", "w");
#endif
    }
    void TearDown() override {
        remove(fileName.c_str());
        fclose(inputFile);
        fclose(outputFile);
    }
};



#endif //CUSTOMERTESTS_H
