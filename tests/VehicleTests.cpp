#include "VehicleTests.h"
#include "Utils.h"

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
    insertVehicle(nullptr, vehicles.data(), &quantity);
    EXPECT_EQ(quantity, MAX_VEHICLES);
}

TEST_F(VehicleTests, InsertVehicleValid) {
    size_t quantity {vehicles.size() - 1};
    FILE *file = Utils::createInputFile("Tesla\nModel S\nTest\n0\n1\n");
    insertVehicle(file, vehicles.data(), &quantity);
    EXPECT_EQ(quantity, MAX_VEHICLES);
    EXPECT_EQ(vehicles.at(vehicles.size() - 1).code, MAX_VEHICLES - 1);
}

TEST_F(VehicleTests, EditVehicleValid) {
    FILE *file = Utils::createInputFile("0\neTesla\nModel S\nTest\n0\n1\n");
    size_t quantity{vehicles.size()};
    manageVehicleByCode(file, vehicles.data(), &quantity);
    const std::string expected {"Tesla"};
    EXPECT_EQ(vehicles.at(0).brand, expected);
}

TEST_F(VehicleTests, EditVehicleInvalid) {
    FILE *file = Utils::createInputFile("0\neTesla\nModel S\nTest\n0\n1\n");
    size_t quantity{vehicles.size()};
    vehicles.at(0).isUnderContract = true;
    manageVehicleByCode(file, vehicles.data(), &quantity);
    const std::string expected {"Tesla"};
    EXPECT_NE(vehicles.at(0).brand, expected);
}

TEST_F(VehicleTests, DeleteVehicleUnderContract) {
    FILE *file = Utils::createInputFile("0\nd");
    size_t quantity{vehicles.size()};
    strcpy(vehicles.at(0).brand, "Tesla");
    vehicles.at(0).isUnderContract = true;
    manageVehicleByCode(file, vehicles.data(), &quantity);
    const std::string expected {"Tesla"};
    EXPECT_EQ(vehicles.at(0).brand, expected);
    EXPECT_EQ(quantity, vehicles.size());
}

TEST_F(VehicleTests, DeleteVehicleValid) {
    FILE *file = Utils::createInputFile("0\nd");
    size_t quantity{vehicles.size()};
    strcpy(vehicles.at(0).brand, "name");
    manageVehicleByCode(file, vehicles.data(), &quantity);
    const std::string expected {"name"};
    EXPECT_NE(vehicles.at(0).brand, expected);
    EXPECT_NE(quantity, vehicles.size());
}
