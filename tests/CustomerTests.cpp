#include "CustomerTests.h"
#include "Utils.h"
#include <fstream>

TEST_F(CustomerTests, SearchCodeCustomerExistingCode) {
    EXPECT_EQ(searchCodeCustomer(customers.data(), customers.size(), 0), 0);
}

TEST_F(CustomerTests, SearchCodeCustomerUnexistingCode) {
    EXPECT_EQ(searchCodeCustomer(customers.data(), customers.size(), customers.size()), -1);
}

TEST_F(CustomerTests, InsertCustomerMaxCustomersReached) {
    size_t quantity {customers.size()};
    insertCustomer(nullptr, customers.data(), &quantity);
    EXPECT_EQ(quantity, MAX_CUSTOMERS);
}

TEST_F(CustomerTests, InsertCustomerValid) {
    size_t quantity {customers.size() - 1};
    FILE *file = Utils::createInputFile("name\naddress\nlicense");
    insertCustomer(file, customers.data(), &quantity);
    EXPECT_EQ(quantity, MAX_CUSTOMERS);
    EXPECT_EQ(customers.at(customers.size() - 1).code, MAX_CUSTOMERS - 1);
}

TEST_F(CustomerTests, EditCustomerValid) {
    FILE *file = Utils::createInputFile("0\nename\naddress\nlicense");
    size_t quantity{customers.size()};
    showCustomerByCodeAndShowOptions(file, customers.data(), &quantity);
    const std::string expected {"name"};
    EXPECT_EQ(customers.at(0).name, expected);
}

TEST_F(CustomerTests, EditCustomerInvalid) {
    FILE *file = Utils::createInputFile("0\nename\naddress\nlicense");
    size_t quantity{customers.size()};
    customers.at(0).isUnderContract = true;
    showCustomerByCodeAndShowOptions(file, customers.data(), &quantity);
    const std::string expected {"name"};
    EXPECT_NE(customers.at(0).name, expected);
}

TEST_F(CustomerTests, DeleteCustomerUnderContract) {
    FILE *file = Utils::createInputFile("0\nd");
    size_t quantity{customers.size()};
    strcpy(customers.at(0).name, "name");
    customers.at(0).isUnderContract = true;
    showCustomerByCodeAndShowOptions(file, customers.data(), &quantity);
    const std::string expected {"name"};
    EXPECT_EQ(customers.at(0).name, expected);
    EXPECT_EQ(quantity, customers.size());
}

TEST_F(CustomerTests, DeleteCustomerValid) {
    FILE *file = Utils::createInputFile("0\nd");
    size_t quantity{customers.size()};
    strcpy(customers.at(0).name, "name");
    showCustomerByCodeAndShowOptions(file, customers.data(), &quantity);
    const std::string expected {"name"};
    EXPECT_NE(customers.at(0).name, expected);
    EXPECT_NE(quantity, customers.size());
}

TEST_F(CustomerTests, WriteSingleCustomer) {
    char fileName[20] = "test_file";
    writeCustomers(fileName, customers.data(), 1);
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
    }
    const std::streamsize size = file.tellg();
    ASSERT_EQ(size, sizeof(customer));
}

TEST_F(CustomerTests, WriteMaximumCustomers) {
    char fileName[20] = "test_file";
    writeCustomers(fileName, customers.data(), customers.size());
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
    }
    const std::streamsize size = file.tellg();
    ASSERT_EQ(size, MAX_CUSTOMERS * sizeof(customer));
}
