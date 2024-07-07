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
