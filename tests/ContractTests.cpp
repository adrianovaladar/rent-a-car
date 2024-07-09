#include "ContractTests.h"
#include "Utils.h"

TEST_F(ContractTests, StartContractWithoutCustomers) {
    size_t quantityContracts {};
    constexpr size_t quantityCustomers{};
    startContract(nullptr, contracts.data(), customers.data(), vehicles.data(), &quantityContracts, quantityCustomers, vehicles.size());
    EXPECT_EQ(quantityContracts, 0);
}

TEST_F(ContractTests, StartContractWithoutVehicles) {
    size_t quantityContracts {};
    constexpr size_t quantityVehicles{};
    startContract(nullptr, contracts.data(), customers.data(), vehicles.data(), &quantityContracts, customers.size(), quantityVehicles);
    EXPECT_EQ(quantityContracts, 0);
}

TEST_F(ContractTests, StartContractMaxContractsReached) {
    size_t quantityContracts {contracts.size()};
    startContract(nullptr, contracts.data(), customers.data(), vehicles.data(), &quantityContracts, customers.size(), vehicles.size());
    EXPECT_EQ(quantityContracts, contracts.size());
}

TEST_F(ContractTests, StartContractRiskyClient) {
    FILE *file = Utils::createInputFile("0\n0\n1.0\n2024/1/1/n");
    size_t quantityContracts {};
    customers[0].isRisky = true;
    startContract(file, contracts.data(), customers.data(), vehicles.data(), &quantityContracts, customers.size(), vehicles.size());
    EXPECT_EQ(quantityContracts, 0);
}

TEST_F(ContractTests, StartContractVehicleUnderContract) {
    FILE *file = Utils::createInputFile("0\n0\n1.0\n2024/1/1/n");
    size_t quantityContracts {};
    vehicles[0].isUnderContract = true;
    startContract(file, contracts.data(), customers.data(), vehicles.data(), &quantityContracts, customers.size(), vehicles.size());
    EXPECT_EQ(quantityContracts, 0);
}

TEST_F(ContractTests, StartContractValid) {
    FILE *file = Utils::createInputFile("0\n0\n1.0\n2024\n1\n1/n");
    size_t quantityContracts {};
    startContract(file, contracts.data(), customers.data(), vehicles.data(), &quantityContracts, customers.size(), vehicles.size());
    EXPECT_EQ(quantityContracts, 1);
    EXPECT_EQ(contracts[0].startDate.year, 2024);
}

TEST_F(ContractTests, ManageContractWithoutContracts) {
    FILE *file = Utils::createInputFile("d");
    size_t quantityContracts {};
    manageContractByVehicleCodeAndStartDate(file, contracts.data(), vehicles.data(), customers.data(), &quantityContracts, vehicles.size(), customers.size());
    EXPECT_EQ(quantityContracts, 0);
}

TEST_F(ContractTests, DeleteContractOngoing) {
    FILE *file = Utils::createInputFile("0\n0\n1.0\n2024\n1\n1/n");
    size_t quantityContracts {};
    startContract(file, contracts.data(), customers.data(), vehicles.data(), &quantityContracts, customers.size(), vehicles.size());
    file = Utils::createInputFile("2024\n1\n1\n0d");
    manageContractByVehicleCodeAndStartDate(file, contracts.data(), vehicles.data(), customers.data(), &quantityContracts, vehicles.size(), customers.size());
    EXPECT_EQ(quantityContracts, 1);
}

TEST_F(ContractTests, DeleteContractValid) {
    FILE *file = Utils::createInputFile("0\n0\n1.0\n2024\n1\n1/n");
    size_t quantityContracts {};
    startContract(file, contracts.data(), customers.data(), vehicles.data(), &quantityContracts, customers.size(), vehicles.size());
    contracts[quantityContracts - 1].endDate.day = 2;
    contracts[quantityContracts - 1].endDate.month = 1;
    contracts[quantityContracts - 1].endDate.year = 2024;
    file = Utils::createInputFile("2024\n1\n1\n0d");
    manageContractByVehicleCodeAndStartDate(file, contracts.data(), vehicles.data(), customers.data(), &quantityContracts, vehicles.size(), customers.size());
    EXPECT_EQ(quantityContracts, 0);
}

TEST_F(ContractTests, EditContractClosed) {
    FILE *file = Utils::createInputFile("0\n0\n1.0\n2024\n1\n1/n");
    size_t quantityContracts {};
    startContract(file, contracts.data(), customers.data(), vehicles.data(), &quantityContracts, customers.size(), vehicles.size());
    date expectedDate;
    expectedDate.day = contracts.at(quantityContracts - 1).startDate.day;
    expectedDate.month = contracts.at(quantityContracts - 1).startDate.month;
    expectedDate.year = contracts.at(quantityContracts - 1).startDate.year;
    const float expectedPrice = contracts.at(quantityContracts - 1).price;
    contracts.at(quantityContracts - 1).endDate.day = 2;
    contracts.at(quantityContracts - 1).endDate.month = 1;
    contracts.at(quantityContracts - 1).endDate.year = 2024;
    file = Utils::createInputFile("2024\n1\n1\n0e");
    manageContractByVehicleCodeAndStartDate(file, contracts.data(), vehicles.data(), customers.data(), &quantityContracts, vehicles.size(), customers.size());
    EXPECT_EQ(areDatesEqual(expectedDate, contracts.at(quantityContracts - 1).startDate), true);
    EXPECT_EQ(expectedPrice, contracts.at(quantityContracts - 1).price);
}

TEST_F(ContractTests, EditContractValid) {
    FILE *file = Utils::createInputFile("0\n0\n1.0\n2024\n1\n1/n");
    size_t quantityContracts {};
    startContract(file, contracts.data(), customers.data(), vehicles.data(), &quantityContracts, customers.size(), vehicles.size());
    date unexpectedDate;
    unexpectedDate.day = contracts.at(quantityContracts - 1).startDate.day;
    unexpectedDate.month = contracts.at(quantityContracts - 1).startDate.month;
    unexpectedDate.year = contracts.at(quantityContracts - 1).startDate.year;
    const float unexpectedPrice = contracts.at(quantityContracts - 1).priceDay;
    file = Utils::createInputFile("2024\n1\n1\n0e2.0\n2025\n1\n1\n");
    manageContractByVehicleCodeAndStartDate(file, contracts.data(), vehicles.data(), customers.data(), &quantityContracts, vehicles.size(), customers.size());
    EXPECT_NE(areDatesEqual(unexpectedDate, contracts.at(quantityContracts - 1).startDate), true);
    EXPECT_NE(unexpectedPrice, contracts.at(quantityContracts - 1).priceDay);
}
