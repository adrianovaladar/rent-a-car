#ifndef RENT_A_CAR_VEHICLE_H
#define RENT_A_CAR_VEHICLE_H

#include "constants.h"
#include <glob.h>
#include <stdbool.h>

enum office { Braga = 0,
              Coimbra = 1,
              Guarda = 2,
              Faro = 3,
              Lisbon = 4,
              Porto = 5 };

typedef struct vehicle {
    int code;
    char brand[10];
    char model[10];
    char registrationPlate[9];
    int codeCategory;// check this
    float km;
    float quantityFuel;
    int location;
    bool isUnderContract;
} vehicle;

void insertVehicle(vehicle v[], size_t *qtd, int local[][MAX_OFFICES]);
void showAllVehicles(vehicle v[], size_t qtd);
void showVehicleByCodeAndShowOptions(vehicle vehicles[], size_t qtd, int local[][6]);
int searchCodeVehicle(vehicle vec[], size_t qtd, int code);

#endif//RENT_A_CAR_VEHICLE_H
