#include "vehicle.h"
#include "constants.h"
#include "input.h"
#include <stdio.h>
#include <string.h>

char *officeEnumToText(enum office o) {
    if (o == Unknown)
        return "Unknown\0";
    else if (o == Porto)
        return "Porto\0";
    else if (o == Guarda)
        return "Guarda\0";
    else if (o == Coimbra)
        return "Coimbra\0";
    else if (o == Braga)
        return "Braga\0";
    else if (o == Faro)
        return "Faro\0";
    else if (o == Lisbon)
        return "Lisbon\0";
}

static void readVehicleData(vehicle *v) {
    readString(v->brand, 10, "Brand (maximum 10 characters):");
    readString(v->model, 10, "Model (maximum 10 characters):");
    readString(v->registrationPlate, 8, "Registration plate (maximum 8 characters):");// check behaviour
    printf("\nCategory code:\n");
    v->codeCategory = readInt(0, 6);
    v->isUnderContract = false;
    if (v->codeCategory < 4) {
        printf("\nKms:\n");
        v->km = readFloat(0, 9999);
        printf("\nAmount of fuel:\n");
        v->quantityFuel = readFloat(0, 9999);
    } else {
        v->km = 0;
        v->quantityFuel = 0;
    }
    printf("Office where the vehicle is:\n");
    printf("%s %d %s %d %s %d %s %d %s %d %s %d", officeEnumToText(Braga), Braga, officeEnumToText(Coimbra), Coimbra, officeEnumToText(Guarda), Guarda, officeEnumToText(Faro), Faro, officeEnumToText(Lisbon), Lisbon, officeEnumToText(Porto), Porto);
    v->location = readInt(0, 5);
}

int searchCodeVehicle(vehicle vehicles[], size_t quantity, int code) {
    int i, enc = -1;

    for (i = 0; i <= quantity && enc == -1; i++)
        if (vehicles[i].code == code)
            enc = i;

    return enc;
}

static void setCodeNewVehicle(vehicle vehicles[], size_t *quantity) {
    vehicles[*quantity].code = 0;
    for (size_t i = 0; i < *quantity; i++) {
        if (vehicles[i].code == vehicles[*quantity].code)
            vehicles[*quantity].code++;
    }
}

void insertVehicle(vehicle vehicles[], size_t *quantity) {
    int n, position;
    if (*quantity == MAX_VEHICLES) {
        printf("\nThe stand is full, please como back later\n");
        return;
    }
    printf("--- Car data ---\n");
    setCodeNewVehicle(vehicles, quantity);
    printf("Code: %d\n", vehicles[*quantity].code);
    readVehicleData(&vehicles[*quantity]);
    (*quantity)++;
}

static void editVehicle(vehicle *v) {
    if (v->isUnderContract) {
        printf("\nThe vehicle is under a contract at the moment, please come back later\n");
        return;
    }
    printf("--- Car data ---\n");
    readVehicleData(v);
}

static void deleteVehicle(vehicle vehicles[], int pos, size_t *qtd) {
    if (vehicles[pos].isUnderContract) {
        printf("\nThe vehicle is under a contract at the moment, please come back later\n");
        return;
    }
    for (int i = pos; i <= *qtd; i++) {
        vehicles[i] = vehicles[i + 1];
    }
    (*qtd)--;
}

static void showVehicle(vehicle v) {
    printf("\n--- Car data ---\n");
    printf("\nCode: %d", v.code);
    printf("\nBrand: %s", v.brand);
    printf("\nModel: %s", v.model);
    printf("\nRegistration plate: %s", v.registrationPlate);
    printf("\nCategory code: %d", v.codeCategory);
    printf("\nKms: %.2f", v.km);
    printf("\nAmount of fuel: %.2f", v.quantityFuel);
    printf("\nStatus: %s\n", v.isUnderContract ? "Unavailable" : "Available");
}

void showVehicleByCodeAndShowOptions(vehicle vehicles[], size_t quantity) {
    int n, codeFound;

    if (quantity == 0) {
        printf("\nThere are no registered vehicles\n");
        return;
    }
    n = readInt(10, 99);
    codeFound = searchCodeVehicle(vehicles, quantity, n);
    if (codeFound >= 0) {
        showVehicle(vehicles[codeFound]);
        printf("\nEdit(e) Delete(d) (Press any other key plus enter to leave this menu)\n");
        unsigned char op;
        do {
            op = getchar();
        } while (op == '\n');
        if (op == 'E' || op == 'e') {
            editVehicle(&vehicles[codeFound]);
        } else if (op == 'D' || op == 'd') {
            deleteVehicle(vehicles, codeFound, &quantity);
            printf("Vehicle deleted successfully\n");
        }
    } else {
        printf("No vehicle found with code %d\n", n);
    }
}

void showAllVehicles(vehicle vehicles[], size_t quantity) {
    int i;
    if (quantity == 0) {
        printf("\nThere are no registered vehicles\n");
        getchar();
    } else
        for (i = 0; i < quantity; i++) {
            showVehicle(vehicles[i]);
        }
}

void showVehiclesLocation(vehicle vehicles[], size_t quantityVehicles) {

    int i, j;
    printf("              |                             OFFICES                          |\n");
    printf("VEHICLES      |Braga   |Coimbra |Guarda  |Faro    |Lisbon  |Porto   |Unknown |\n");
    printf("--------------|--------|--------|--------|--------|--------|--------|--------|\n");
    for (i = 0; i < quantityVehicles; i++) {
        printf("%-5d", vehicles[i].code);
        printf("         |");
        for (j = 0; j < MAX_OFFICES; j++) {
            char text[10] = "\0";
            strcat(text, "    \0");
            text[4] = j == vehicles[i].location ? 'x' : ' ';
            strcat(text, "   |\0");
            printf("%s", text);
        }
        printf("\n");
    }
}
