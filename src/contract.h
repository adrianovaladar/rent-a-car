#ifndef RENT_A_CAR_CONTRACT_H
#define RENT_A_CAR_CONTRACT_H

#include "customer.h"
#include "date.h"
#include "vehicle.h"

typedef struct contract {
    int codeVehicle;
    int codeCustomer;
    float priceDay;
    float priceKm;
    float quantityKm;
    date startDate;
    date endDate;
    int startOffice;
    int endOffice;
} contract;

void showContractData(contract c[], size_t qtd);
void showContract(contract c);
void editContract(contract cont[], vehicle vec[], int pos, date d[], size_t qtdvec, size_t qtd);
void deleteContract(contract c[], int pos, size_t *qtd);
int ShowContract(contract c[], date data[], size_t qtd);
int searchDate(contract cont[], date data[], size_t qtd);
void startContract(contract contracts[], customer customers[], vehicle vehicles[], date data[], size_t qtdcli, size_t qtdvec, size_t *qtd);
void endContract(contract contracts[], int pos, date data[], vehicle vehicles[], customer customers[], int quantityCustomers, int quantityVehicles, int quantityContracts);

#endif//RENT_A_CAR_CONTRACT_H
