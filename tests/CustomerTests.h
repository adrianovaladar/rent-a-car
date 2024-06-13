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
    void SetUp() override {
        for(int i {}; i < MAX_CUSTOMERS; i++) {
            customers[i].code = i;
        }
    }
    void TearDown() override {
    }
};



#endif //CUSTOMERTESTS_H
