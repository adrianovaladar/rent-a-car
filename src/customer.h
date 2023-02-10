#ifndef RENT_A_CAR_CUSTOMER_H
#define RENT_A_CAR_CUSTOMER_H

#include <glob.h>
#include <stdbool.h>

typedef struct customer {
    int code;
    char name[30];
    char address[40];
    bool type;
    char driverLicense[11];
    bool isUnderContract;

} customer;

void insertCustomer(customer customers[], size_t *quantity);
void showCustomerByCodeAndShowOptions(customer customers[], size_t quantity);
void showAllCustomers(customer customers[], size_t quantity);
int searchCodeCustomer(customer customers[], size_t quantity, int code);
void readCustomers(char *fileName, customer customers[], size_t *quantity);
void writeCustomers(char *fileName, customer customers[], size_t quantity);

#endif//RENT_A_CAR_CUSTOMER_H
