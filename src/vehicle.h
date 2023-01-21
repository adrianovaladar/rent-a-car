#ifndef RENT_A_CAR_VEHICLE_H
#define RENT_A_CAR_VEHICLE_H

#include "constants.h"
#include <glob.h>
#include <stdbool.h>

typedef struct vehicle {
    int code;
    char brand[10];
    char model[10];
    char registrationPlate[9];
    int codeCategory;// check this
    float km;
    float quantityFuel;
    int startPlace;
    bool isUnderContract;
} vehicle;

void insertVehicle(vehicle v[], size_t *qtd, int local[][MAX_OFFICES]);
int searchCodeVehicle(vehicle vec[], size_t qtd, int code);
void editVehicle(vehicle vec[], int pos, int local[][MAX_OFFICES]);
void deleteVehicle(vehicle vec[], int pos, size_t *qtd, int local[][6]);
void showVehicle(vehicle vec);
void showAllVehicles(vehicle vec[], size_t qtd);
int showVehicleByCode(vehicle vec[], size_t qtd);

#endif//RENT_A_CAR_VEHICLE_H
