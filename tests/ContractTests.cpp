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
    FILE *file = Utils::createInputFile("0\n0\n1.0\n2024/1/1/n");
    size_t quantityContracts {};
    startContract(file, contracts.data(), customers.data(), vehicles.data(), &quantityContracts, customers.size(), vehicles.size());
    EXPECT_EQ(quantityContracts, 1);
    EXPECT_EQ(contracts[0].startDate.year, 2024);
}
