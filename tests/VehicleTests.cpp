#include "VehicleTests.h"

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
