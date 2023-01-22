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
void editVehicle(vehicle *v, int pos, int local[][6]);
void deleteVehicle(vehicle v[], int pos, size_t *qtd, int local[][6]);
void showVehicle(vehicle v);
void showAllVehicles(vehicle v[], size_t qtd);
void showVehicleByCode(vehicle v[], size_t qtd, int local[][6]);

#endif//RENT_A_CAR_VEHICLE_H
