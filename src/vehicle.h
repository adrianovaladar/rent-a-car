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
    char brand[11];
    char model[11];
    char registrationPlate[9];
    float km;
    int location;
    bool isUnderContract;
} vehicle;

void insertVehicle(vehicle vehicles[], size_t *quantity);
void showAllVehicles(vehicle vehicles[], size_t quantity);
void showVehicleByCodeAndShowOptions(vehicle vehicles[], size_t *quantity);
int searchCodeVehicle(vehicle vehicles[], size_t quantity, int code);
void showVehiclesLocation(vehicle vehicles[], size_t quantity);
char *officeEnumToText(enum office o);
void readVehicles(char *fileName, vehicle vehicles[], size_t *quantity);
void writeVehicles(char *fileName, vehicle vehicles[], size_t quantity);

#endif//RENT_A_CAR_VEHICLE_H
