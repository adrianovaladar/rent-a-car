#ifndef RENT_A_CAR_VEHICLE_H
#define RENT_A_CAR_VEHICLE_H

#include <glob.h>
#include <stdbool.h>
#include <stdio.h>

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

void insertVehicle(FILE *file, vehicle *vehicles, size_t *quantity);
void showAllVehicles(const vehicle *vehicles, size_t quantity);
void manageVehicleByCode(FILE *file, vehicle *vehicles, size_t *quantity);
int searchCodeVehicle(const vehicle *vehicles, size_t quantity, int code);
void showVehiclesLocation(const vehicle *vehicles, size_t quantity);
char *officeEnumToText(enum office o);
void readVehicles(const char *fileName, vehicle *vehicles, size_t *quantity);
void writeVehicles(const char *fileName, const vehicle *vehicles, size_t quantity);

#endif//RENT_A_CAR_VEHICLE_H
