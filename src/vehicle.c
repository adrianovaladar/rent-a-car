#include "vehicle.h"
#include "constants.h"
#include "input.h"
#include <stdio.h>
#include <string.h>

void insertVehicle(vehicle vec[], int *qtd, int local[][MAX_ESC]) {
    int n, found;
    char value[MAX_TXT];
    if (*qtd == MAX_VC) {
        printf("\nThe stand is full, please como back later\n");
        return;
    }
    printf("\n--- Car data ---");
    n = readInt(10, 99);
    found = searchCodeVehicle(vec, *qtd, n);
    printf("\n\t\t found %d and *qtd %d ", found, *qtd);
    while (found >= 0) {
        n = readInt(10, 99);
        found = searchCodeVehicle(vec, *qtd, n);
    }
    vec[*qtd].code = n;
    readString(value, 10, "\nBrand (maximum 10 characters):");
    printf("\n\t %s ", value);
    strcpy(vec[*qtd].brand, value);
    readString(value, 10, "\nModel (maximum 10 characters):");
    printf("\n\t %s ", value);
    strcpy(vec[*qtd].model, value);
    readString(value, 8, "\nRegistration plate (maximum 8 characters):");
    printf("\n\t %s ", value);
    strcpy(vec[*qtd].registrationPlate, value);
    printf("\nCategory code:\n");
    vec[*qtd].codeCategory = readInt(0, 6);
    vec[*qtd].isUnderContract = false;
    if (vec[*qtd].codeCategory < 4) {
        printf("\nKms:\n");
        vec[*qtd].km = readFloat(0, 9999);
        printf("\nAmount of fuel:\n");
        vec[*qtd].quantityFuel = readFloat(0, 9999);
    }
    printf("\nOffice where the vehicle is:");
    printf("\n0 Braga 1 Coimbra 2 Guarda 3 Faro 4 Lisboa 5 Porto");
    n = readInt(0, 5);
    (local[*qtd][n])++;
    vec[*qtd].startPlace = n;
    (*qtd)++;
}

int searchCodeVehicle(vehicle vec[], int qtd, int code) {
    int i, enc = -1;

    for (i = 0; i <= qtd && enc == -1; i++)
        if (vec[i].code == code)
            enc = i;

    return enc;
}

void editVehicle(vehicle vec[], int pos, int local[][MAX_ESC]) {
    if (vec[pos].isUnderContract) {
        printf("\nThe vehicle is under a contract at the moment, please come back later\n");
        return;
    }
    int n, i;
    char value[MAX_TXT];
    printf("\n--- Car data ---");
    readString(value, 10, "\nBrand (maximum 10 characters:");
    //  printf("\n\t %s ", value);
    strcpy(vec[pos].brand, value);
    readString(value, 10, "\nModel (maximum 10 characters):");
    printf("\n\t %s ", value);
    strcpy(vec[pos].model, value);
    readString(value, 8, "\nRegistration plate (maximum 8 characters):");
    printf("\n\t %s ", value);
    strcpy(vec[pos].registrationPlate, value);
    printf("\nCategory code:\n");
    vec[pos].codeCategory = readInt(0, 6);
    if (vec[pos].codeCategory < 4) {
        printf("\nKms:\n");
        vec[pos].km = readFloat(0, 9999);
        printf("\nAmount of fuel:\n");
        vec[pos].quantityFuel = readFloat(0, 9999);
    } else if (vec[pos].codeCategory >= 4) {
        vec[pos].km = 0;
        vec[pos].quantityFuel = 0;
    }
    for (i = 0; i < MAX_ESC; i++) {
        if (local[pos][i] == 1)
            (local[pos][i])--;
    }
    printf("\nOffice where the vehicle is:");
    printf("\n0 Braga 1 Coimbra 2 Guarda 3 Faro 4 Lisboa 5 Porto");
    n = readInt(0, 5);
    (local[pos][n])++;
    vec[pos].startPlace = n;
}

void deleteVehicle(vehicle vec[], int pos, int *qtd, int local[][6]) {
    if (vec[pos].isUnderContract) {
        printf("\nThe vehicle is under a contract at the moment, please come back later\n");
        return;
    }
    for (int i = pos; i <= *qtd; i++) {
        vec[i] = vec[i + 1];
    }
    (*qtd)--;

    for (int i = 0; i < MAX_ESC; i++) {
        if (local[pos][i] == 1)
            (local[pos][i])--;
    }
}

void showVehicle(vehicle vec) {
    printf("\n--- Car data ---\n");
    printf("\n Code: %d", vec.code);
    printf("\n Brand: %s", vec.brand);
    printf("\n Model: %s", vec.model);
    printf("\n Registration plate: %s", vec.registrationPlate);
    printf("\n Category code: %d", vec.codeCategory);
    printf("\n Kms: %.2f", vec.km);
    printf("\n Amount of fuel: %.2f", vec.quantityFuel);
    printf("\n Status: %s\n", vec.isUnderContract ? "Unavailable" : "Available");
}

void showAllVehicles(vehicle vec[], int qtd) {
    int i;
    if (qtd == 0) {
        printf("\nThere are no registered vehicles\n");
        getchar();
    } else
        for (i = 0; i < qtd; i++) {
            showVehicle(vec[i]);
            getchar();
        }
}

int showVehicleByCode(vehicle vec[], int qtd) {
    int n, found = -1;
    if (qtd == 0)
        printf("\nThere are no registered vehicles\n");
    else {
        n = readInt(10, 99);
        found = searchCodeVehicle(vec, qtd, n);
        if (found >= 0)
            showVehicle(vec[found]);
        else
            printf("\nNo vehicle found with code %d\n", n);
    }
    getchar();
    return found;
}
