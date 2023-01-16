#ifndef RENT_A_CAR_CUSTOMER_H
#define RENT_A_CAR_CUSTOMER_H

typedef struct customer {
    int code;
    char name[30];
    char address[40];
    int type;
    char driverLicense[11];
} customer;

int searchCodeClient(customer cli[], int qtd, int cod);

#endif//RENT_A_CAR_CUSTOMER_H
