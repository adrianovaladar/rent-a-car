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
              Porto = 5,
              Unknown = 6 };

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

void insertVehicle(vehicle vehicles[], size_t *qtd);
void showAllVehicles(vehicle v[], size_t qtd);
void showVehicleByCodeAndShowOptions(vehicle vehicles[], size_t qtd);
int searchCodeVehicle(vehicle vec[], size_t qtd, int code);
void showVehiclesLocation(vehicle v[], size_t quantityVehicles);
char *officeEnumToText(enum office o);

#endif//RENT_A_CAR_VEHICLE_H
