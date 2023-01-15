#ifndef RENT_A_CAR_VEHICLE_H
#define RENT_A_CAR_VEHICLE_H

#include "constants.h"
#include <stdbool.h>

typedef struct vehicle {
    int code;
    char brand[10];
    char model[10];
    char registrationPlate[8];
    int codeCategory;
    float km;
    float quantityFuel;
    char status;
    int startPlace;
    bool isUnderContract;
} vehicle;

void insertVehicle(vehicle vec[], int *qtd, int local[][MAX_ESC]);
int searchCodeVehicle(vehicle vec[], int qtd, int cod);
void editVehicle(vehicle vec[], int pos, int local[][MAX_ESC]);
void deleteVehicle(vehicle vec[], int pos, int *qtd, int local[][6]);
void showVehicle(vehicle vec);
void showAllVehicles(vehicle vec[], int qtd);
int showVehicleByCode(vehicle vec[], int qtd);

#endif//RENT_A_CAR_VEHICLE_H
