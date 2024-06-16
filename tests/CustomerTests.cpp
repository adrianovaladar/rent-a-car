#include "CustomerTests.h"
#include "Utils.h"

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
