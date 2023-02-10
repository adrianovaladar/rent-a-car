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
    readString(v->brand, 11, "Brand (maximum 10 characters):");
    readString(v->model, 11, "Model (maximum 10 characters):");
    readString(v->registrationPlate, 9, "Registration plate (maximum 8 characters):");
    v->isUnderContract = false;
    printf("Kms:\n");
    v->km = readFloat(0, 9999);
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

static void setCodeNewVehicle(vehicle vehicles[], const size_t *quantity) {
    vehicles[*quantity].code = 0;
    for (size_t i = 0; i < *quantity; i++) {
        if (vehicles[i].code == vehicles[*quantity].code)
            vehicles[*quantity].code++;
    }
}

void insertVehicle(vehicle vehicles[], size_t *quantity) {
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
    printf("\nKms: %.2f", v.km);
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

void readVehicles(char *fileName, vehicle vehicles[], size_t *quantity) {
    FILE *file;
    file = fopen(fileName, "rb");
    if (file == NULL) {
        printf("Error opening file '%s'!\n", fileName);
        return;
    }

    // calculate the number of vehicles
    fseek(file, 0, SEEK_END);
    *quantity = ftell(file) / sizeof(vehicle);

    // set the file position back to the beginning
    rewind(file);

    // check that the number of vehicles is not negative or bigger than expected
    if (*quantity < 0 || *quantity > MAX_VEHICLES) {
        printf("Error: invalid file size in '%s'\n", fileName);
        fclose(file);
        return;
    }

    // read the vehicles
    fread(vehicles, sizeof(vehicle), *quantity, file);

    fclose(file);
}

// function to write vehicles to a binary file
void writeVehicles(char *fileName, vehicle vehicles[], size_t quantity) {
    FILE *file;
    file = fopen(fileName, "wb");
    if (file == NULL) {
        printf("Error opening file '%s'!\n", fileName);
        return;
    }

    // write the vehicles
    fwrite(vehicles, sizeof(vehicle), quantity, file);

    fclose(file);
}
