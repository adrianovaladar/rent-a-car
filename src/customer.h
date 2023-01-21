#ifndef RENT_A_CAR_CUSTOMER_H
#define RENT_A_CAR_CUSTOMER_H

#include <stdbool.h>

typedef struct customer {
    int code;
    char name[30];
    char address[40];
    bool type;
    char driverLicense[11];
    bool isUnderContract;

} customer;

void insertCustomer(customer c[], int *qtd);
void showCustomerByCode(customer c[], int qtd);
void showAllCustomers(customer c[], int qtd);

#endif//RENT_A_CAR_CUSTOMER_H
