#include "VehicleTests.h"
#include "Utils.h"
#include <fstream>

TEST(VehicleTest, OfficeEnumToText) {
    EXPECT_EQ(officeEnumToText(Braga), std::string("Braga"));
    EXPECT_EQ(officeEnumToText(Coimbra), std::string("Coimbra"));
    EXPECT_EQ(officeEnumToText(Faro), std::string("Faro"));
    EXPECT_EQ(officeEnumToText(Guarda), std::string("Guarda"));
    EXPECT_EQ(officeEnumToText(Lisbon), std::string("Lisbon"));
    EXPECT_EQ(officeEnumToText(Unknown), std::string("Unknown"));
    EXPECT_EQ(officeEnumToText(static_cast<office>(7)), std::string("Invalid"));
}

TEST_F(VehicleTests, SearchCodeVehicleExistingCode) {
    EXPECT_EQ(searchCodeVehicle(vehicles.data(), vehicles.size(), 0), 0);
}

TEST_F(VehicleTests, SearchCodeVehicleUnexistingCode) {
    EXPECT_EQ(searchCodeVehicle(vehicles.data(), vehicles.size(), vehicles.size()), -1);
}

TEST_F(VehicleTests, InsertVehicleMaxVehiclesReached) {
    size_t quantity {vehicles.size()};
    insertVehicle(nullptr, outputFile, vehicles.data(), &quantity);
    EXPECT_EQ(quantity, MAX_VEHICLES);
}

TEST_F(VehicleTests, InsertVehicleValid) {
    size_t quantity {vehicles.size() - 1};
    inputFile = Utils::createInputFile("Tesla\nModel S\nTest\n0\n1\n");
    insertVehicle(inputFile, outputFile, vehicles.data(), &quantity);
    EXPECT_EQ(quantity, MAX_VEHICLES);
    EXPECT_EQ(vehicles.at(vehicles.size() - 1).code, MAX_VEHICLES - 1);
}

TEST_F(VehicleTests, EditVehicleValid) {
    inputFile = Utils::createInputFile("0\neTesla\nModel S\nTest\n0\n1\n");
    size_t quantity{vehicles.size()};
    manageVehicleByCode(inputFile, outputFile, vehicles.data(), &quantity);
    const std::string expected {"Tesla"};
    EXPECT_EQ(vehicles.at(0).brand, expected);
}

TEST_F(VehicleTests, EditVehicleInvalid) {
    inputFile = Utils::createInputFile("0\neTesla\nModel S\nTest\n0\n1\n");
    size_t quantity{vehicles.size()};
    vehicles.at(0).isUnderContract = true;
    manageVehicleByCode(inputFile, outputFile, vehicles.data(), &quantity);
    const std::string expected {"Tesla"};
    EXPECT_NE(vehicles.at(0).brand, expected);
}

TEST_F(VehicleTests, DeleteVehicleUnderContract) {
    inputFile = Utils::createInputFile("0\nd");
    size_t quantity{vehicles.size()};
    strcpy(vehicles.at(0).brand, "Tesla");
    vehicles.at(0).isUnderContract = true;
    manageVehicleByCode(inputFile, outputFile, vehicles.data(), &quantity);
    const std::string expected {"Tesla"};
    EXPECT_EQ(vehicles.at(0).brand, expected);
    EXPECT_EQ(quantity, vehicles.size());
}

TEST_F(VehicleTests, DeleteVehicleValid) {
    inputFile = Utils::createInputFile("0\nd");
    size_t quantity{vehicles.size()};
    strcpy(vehicles.at(0).brand, "name");
    manageVehicleByCode(inputFile, outputFile, vehicles.data(), &quantity);
    const std::string expected {"name"};
    EXPECT_NE(vehicles.at(0).brand, expected);
    EXPECT_NE(quantity, vehicles.size());
}

TEST_F(VehicleTests, WriteSingleVehicle) {
    writeVehicles(outputFile, fileName.c_str(), vehicles.data(), 1);
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
    }
    const std::streamsize size = file.tellg();
    ASSERT_EQ(size, sizeof(vehicle));
}

TEST_F(VehicleTests, WriteMaximumVehicles) {
    writeVehicles(outputFile, fileName.c_str(), vehicles.data(), vehicles.size());
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
    }
    const std::streamsize size = file.tellg();
    ASSERT_EQ(size, MAX_VEHICLES * sizeof(vehicle));
}

TEST_F(VehicleTests, ReadSingleVehicle) {
    constexpr int expected {50};
    vehicles.at(0).code = expected;
    writeVehicles(outputFile, fileName.c_str(), vehicles.data(), 1);
    vehicles.at(0).code = 0;
    size_t quantity {};
    readVehicles(outputFile, fileName.c_str(), vehicles.data(), &quantity);
    EXPECT_EQ(vehicles.at(0).code, expected);
    EXPECT_EQ(quantity, 1);
}

TEST_F(VehicleTests, ReadMaximumVehicles) {
    constexpr int expected {50};
    vehicles.at(0).code = expected;
    writeVehicles(outputFile, fileName.c_str(), vehicles.data(), vehicles.size());
    vehicles.at(0).code = 0;
    size_t quantity {};
    readVehicles(outputFile, fileName.c_str(), vehicles.data(), &quantity);
    EXPECT_EQ(vehicles.at(0).code, expected);
    EXPECT_EQ(quantity, vehicles.size());
}
