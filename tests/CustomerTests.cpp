#include "CustomerTests.h"

TEST_F(CustomerTests, SearchCodeCustomerExistingCode) {
    EXPECT_EQ(searchCodeCustomer(customers.data(), customers.size(), 0), 0);
}

TEST_F(CustomerTests, SearchCodeCustomerUnexistingCode) {
    EXPECT_EQ(searchCodeCustomer(customers.data(), customers.size(), customers.size()), -1);
}
