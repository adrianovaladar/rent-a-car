#ifndef VEHICLETESTS_H
#define VEHICLETESTS_H

#include <gtest/gtest.h>
extern "C" {
#include "../src/vehicle.h"
#include "../src/constants.h"
#include "../src/logger.h"
}

class VehicleTests : public ::testing::Test {
protected:
    std::array<vehicle, MAX_VEHICLES> vehicles {};
    std::string fileName {"test_file"};
    FILE* inputFile{};
    FILE* outputFile{};
    logger *l{};
    void SetUp() override {
        for(int i {}; i < MAX_VEHICLES; i++) {
            vehicles[i].code = i;
        }
        inputFile = tmpfile();
#ifdef _WIN32
        outputFile = fopen("NUL", "w");
#else
        outputFile = fopen("/dev/null", "w");
#endif
        l = getLoggerInstance();
    }
    void TearDown() override {
        remove(fileName.c_str());
        fclose(inputFile);
        fclose(outputFile);
    }
};



#endif //VEHICLETESTS_H
