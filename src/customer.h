#ifndef RENT_A_CAR_CUSTOMER_H
#define RENT_A_CAR_CUSTOMER_H

#include <stdbool.h>

typedef struct customer {
    int code;
    char name[30];
    char address[40];
    int type;
    char driverLicense[11];
    bool isUnderContract;

} customer;

int searchCodeClient(customer cli[], int qtd, int cod);
void insertCustomer(customer cli[], int *qtd);
void editCustomer(customer cli[], int pos);
void deleteCustomer(customer cli[], int pos, int *qtd);
void mostrarCli(customer cli);
int mostrarDadosCli(customer cli[], int qtd);
void mostrarDadosClis(customer cli[], int qtd);

#endif//RENT_A_CAR_CUSTOMER_H
