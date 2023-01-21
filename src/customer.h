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

void insertCustomer(customer c[], size_t *qtd);
void showCustomerByCode(customer c[], size_t qtd);
void showAllCustomers(customer c[], size_t qtd);
int searchCodeCustomer(customer c[], size_t qtd, int cod);

#endif//RENT_A_CAR_CUSTOMER_H
