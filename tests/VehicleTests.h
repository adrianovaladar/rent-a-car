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
    void SetUp() override {
        for(int i {}; i < MAX_VEHICLES; i++) {
            vehicles[i].code = i;
        }
    }
};



#endif //VEHICLETESTS_H
