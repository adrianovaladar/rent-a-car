#ifndef RENT_A_CAR_CONTRACT_H
#define RENT_A_CAR_CONTRACT_H

#include "customer.h"
#include "date.h"
#include "vehicle.h"

typedef struct contract {
    int codeVehicle;
    int codeCustomer;
    float priceDay;
    float quantityKm;
    date startDate;
    date endDate;
    int startOffice;
    int endOffice;
    float price;
} contract;

void showContracts(const contract *contracts, size_t quantity);
void startContract(FILE *file, contract *contracts, customer *customers, vehicle *vehicles, size_t *quantityContracts, size_t quantityCustomers, size_t quantityVehicles);
void showContractByVehicleCodeAndStartDateAndShowOptions(contract *contracts, vehicle *vehicles, customer *customers, size_t *quantityContracts, size_t quantityVehicles, size_t quantityCustomers);
void readContracts(char *fileName, contract *contracts, size_t *quantity);
void writeContracts(char *fileName, const contract *contracts, size_t quantity);

#endif//RENT_A_CAR_CONTRACT_H
