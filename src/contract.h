#ifndef RENT_A_CAR_CONTRACT_H
#define RENT_A_CAR_CONTRACT_H

#include "date.h"

typedef struct contract {
    int codeVehicle;
    int codeClient;
    float priceDay;
    float priceKm;
    float quantityKm;
    date startDate;
    date endDate;
    int startOffice;
    int endOffice;
} contract;

#endif//RENT_A_CAR_CONTRACT_H
