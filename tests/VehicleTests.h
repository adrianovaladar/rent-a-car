#ifndef VEHICLETESTS_H
#define VEHICLETESTS_H

#include <gtest/gtest.h>
extern "C" {
#include "../src/vehicle.h"
#include "../src/constants.h"
}

class VehicleTests : public ::testing::Test {
protected:
    std::array<vehicle, MAX_VEHICLES> vehicles {};
    std::string fileName {"test_file"};
    void SetUp() override {
        for(int i {}; i < MAX_VEHICLES; i++) {
            vehicles[i].code = i;
        }
    }
    void TearDown() override {
        remove(fileName.c_str());
    }
};



#endif //VEHICLETESTS_H
