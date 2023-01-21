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

void showContractData(contract c[], int qtd);
void showContract(contract c);
void editContract(contract cont[], vehicle vec[], int pos, date d[], int qtdvec, int qtd);
void deleteContract(contract c[], int pos, int *qtd);
int ShowContract(contract c[], date data[], int qtd);
int searchDate(contract cont[], date data[], int qtd);
void startContract(contract contracts[], customer customers[], vehicle vehicles[], int local[][MAX_OFFICES], date data[], int qtdcli, int qtdvec, int *qtd);
void endContract(contract contracts[], int pos, date data[], vehicle vehicles[], customer customers[], int quantityCustomers, int quantityVehicles, int quantityContracts, int local[][MAX_OFFICES]);

#endif//RENT_A_CAR_CONTRACT_H
