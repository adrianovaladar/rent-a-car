#ifndef RENT_A_CAR_CUSTOMER_H
#define RENT_A_CAR_CUSTOMER_H

#include <glob.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct customer {
    int code;
    char name[30];
    char address[40];
    bool type;
    char driverLicense[11];
    bool isUnderContract;

} customer;

void insertCustomer(FILE *file, customer *customers, size_t *quantity);
void showCustomerByCodeAndShowOptions(FILE *file, customer *customers, size_t *quantity);
void showAllCustomers(const customer *customers, size_t quantity);
int searchCodeCustomer(const customer *customers, size_t quantity, int code);
void readCustomers(const char *fileName, customer *customers, size_t *quantity);
void writeCustomers(const char *fileName, const customer *customers, size_t quantity);

#endif//RENT_A_CAR_CUSTOMER_H
