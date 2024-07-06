#ifndef CONTRACTTESTS_H
#define CONTRACTTESTS_H

#include <gtest/gtest.h>
extern "C" {
#include "../src/contract.h"
#include "../src/constants.h"
}

    class ContractTests : public ::testing::Test {
protected:
    std::array<contract, MAX_CONTRACTS> contracts {};
    std::array<customer, MAX_CUSTOMERS> customers {};
    std::array<vehicle, MAX_VEHICLES> vehicles {};
    std::string fileName {"test_file"};
    void SetUp() override {
        for(int i {}; i < MAX_CUSTOMERS; i++) {
            customers[i].code = i;
        }
        for(int i {}; i < MAX_VEHICLES; i++) {
            vehicles[i].code = i;
        }
    }
    void TearDown() override {
        remove(fileName.c_str());
    }
};



#endif //CONTRACTTESTS_H
