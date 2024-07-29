#include "CustomerTests.h"
#include "Utils.h"
#include <fstream>

TEST_F(CustomerTests, SearchCodeCustomerExistingCode) {
    EXPECT_EQ(searchCodeCustomer(l, customers.data(), customers.size(), 0), 0);
}

TEST_F(CustomerTests, SearchCodeCustomerUnexistingCode) {
    EXPECT_EQ(searchCodeCustomer(l, customers.data(), customers.size(), customers.size()), -1);
}

TEST_F(CustomerTests, InsertCustomerMaxCustomersReached) {
    size_t quantity {customers.size()};
    insertCustomer(nullptr, outputFile, l, customers.data(), &quantity);
    EXPECT_EQ(quantity, MAX_CUSTOMERS);
}

TEST_F(CustomerTests, InsertCustomerValid) {
    size_t quantity {customers.size() - 1};
    inputFile = Utils::createInputFile("name\naddress\nlicense");
    insertCustomer(inputFile, outputFile, l, customers.data(), &quantity);
    EXPECT_EQ(quantity, MAX_CUSTOMERS);
    EXPECT_EQ(customers.at(customers.size() - 1).code, MAX_CUSTOMERS - 1);
}

TEST_F(CustomerTests, EditCustomerValid) {
    inputFile = Utils::createInputFile("0\nename\naddress\nlicense");
    size_t quantity{customers.size()};
    manageCustomerByCode(inputFile, outputFile, l, customers.data(), &quantity);
    const std::string expected {"name"};
    EXPECT_EQ(customers.at(0).name, expected);
}

TEST_F(CustomerTests, EditCustomerInvalid) {
    inputFile = Utils::createInputFile("0\nename\naddress\nlicense");
    size_t quantity{customers.size()};
    customers.at(0).isUnderContract = true;
    manageCustomerByCode(inputFile, outputFile, l, customers.data(), &quantity);
    const std::string expected {"name"};
    EXPECT_NE(customers.at(0).name, expected);
}

TEST_F(CustomerTests, DeleteCustomerUnderContract) {
    inputFile = Utils::createInputFile("0\nd");
    size_t quantity{customers.size()};
    strcpy(customers.at(0).name, "name");
    customers.at(0).isUnderContract = true;
    manageCustomerByCode(inputFile, outputFile, l, customers.data(), &quantity);
    const std::string expected {"name"};
    EXPECT_EQ(customers.at(0).name, expected);
    EXPECT_EQ(quantity, customers.size());
}

TEST_F(CustomerTests, DeleteCustomerValid) {
    inputFile = Utils::createInputFile("0\nd");
    size_t quantity{customers.size()};
    strcpy(customers.at(0).name, "name");
    manageCustomerByCode(inputFile, outputFile, l, customers.data(), &quantity);
    const std::string expected {"name"};
    EXPECT_NE(customers.at(0).name, expected);
    EXPECT_NE(quantity, customers.size());
}

TEST_F(CustomerTests, WriteSingleCustomer) {
    writeCustomers(outputFile, l, fileName.c_str(), customers.data(), 1);
    std::ifstream inputFile(fileName, std::ios::binary | std::ios::ate);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open inputFile: " << fileName << std::endl;
    }
    const std::streamsize size = inputFile.tellg();
    ASSERT_EQ(size, sizeof(customer));
}

TEST_F(CustomerTests, WriteMaximumCustomers) {
    writeCustomers(outputFile, l, fileName.c_str(), customers.data(), customers.size());
    std::ifstream inputFile(fileName, std::ios::binary | std::ios::ate);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open inputFile: " << fileName << std::endl;
    }
    const std::streamsize size = inputFile.tellg();
    ASSERT_EQ(size, MAX_CUSTOMERS * sizeof(customer));
}

TEST_F(CustomerTests, ReadSingleCustomer) {
    constexpr int expected {50};
    customers.at(0).code = expected;
    writeCustomers(outputFile, l, fileName.c_str(), customers.data(), 1);
    customers.at(0).code = 0;
    size_t quantity {};
    readCustomers(outputFile, l, fileName.c_str(), customers.data(), &quantity);
    EXPECT_EQ(customers.at(0).code, expected);
    EXPECT_EQ(quantity, 1);
}

TEST_F(CustomerTests, ReadMaximumCustomers) {
    constexpr int expected {50};
    customers.at(0).code = expected;
    writeCustomers(outputFile, l, fileName.c_str(), customers.data(), customers.size());
    customers.at(0).code = 0;
    size_t quantity {};
    readCustomers(outputFile, l, fileName.c_str(), customers.data(), &quantity);
    EXPECT_EQ(customers.at(0).code, expected);
    EXPECT_EQ(quantity, customers.size());
}
