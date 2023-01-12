#ifndef RENT_A_CAR_VEHICLE_H
#define RENT_A_CAR_VEHICLE_H

#include "constants.h"
#include "contract.h"

typedef struct vehicle {
    int code;
    char brand[10];
    char model[10];
    char registrationPlate[8];
    int codeCategory;
    float km;
    float quantityFuel;
    char state;
    int startPlace;
} vehicle;

void insertVehicle(vehicle vec[], int *qtd, int local[][MAX_ESC]);
int searchCodeVehicle(vehicle vec[], int qtd, int cod);
void editVehicle(vehicle vec[], contract cont[], int pos, int local[][MAX_ESC]);
void deleteVehicle(vehicle vec[], contract cont[], int pos, int *qtd, int local[][MAX_ESC]);
bool isUnderContract(vehicle vec[], contract cont[], int pos);

#endif//RENT_A_CAR_VEHICLE_H
