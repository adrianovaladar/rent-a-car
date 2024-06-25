#include "vehicle.h"
#include "constants.h"
#include "input.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

char *officeEnumToText(const enum office o) {
    if (o == Unknown)
        return "Unknown\0";
    if (o == Porto)
        return "Porto\0";
    if (o == Guarda)
        return "Guarda\0";
    if (o == Coimbra)
        return "Coimbra\0";
    if (o == Braga)
        return "Braga\0";
    if (o == Faro)
        return "Faro\0";
    if (o == Lisbon)
        return "Lisbon\0";
    return "Invalid\0";
}

static void readVehicleData(FILE *file, vehicle *v) {
    readString(file, v->brand, 11, "Brand (maximum 10 characters): ");
    readString(file, v->model, 11, "Model (maximum 10 characters): ");
    readString(file, v->registrationPlate, 9, "Registration plate (maximum 8 characters): ");
    v->isUnderContract = false;
    printf("Kms\n");
    v->km = readFloat(file, 0, INFINITY);
    printf("Office\n");
    printf("%s %d %s %d %s %d %s %d %s %d %s %d\n", officeEnumToText(Braga), Braga, officeEnumToText(Coimbra), Coimbra, officeEnumToText(Guarda), Guarda, officeEnumToText(Faro), Faro, officeEnumToText(Lisbon), Lisbon, officeEnumToText(Porto), Porto);
    v->location = readInt(file, 0, 5);
}

int searchCodeVehicle(const vehicle *vehicles, const size_t quantity, const int code) {
    int position = -1;

    for (int i = 0; i <= quantity && position == -1; i++)
        if (vehicles[i].code == code)
            position = i;

    return position;
}

static void setCodeNewVehicle(vehicle *vehicles, const size_t *quantity) {
    vehicles[*quantity].code = 0;
    for (size_t i = 0; i < *quantity; i++) {
        if (vehicles[i].code == vehicles[*quantity].code)
            vehicles[*quantity].code++;
    }
}

void insertVehicle(FILE *file, vehicle *vehicles, size_t *quantity) {
    if (*quantity == MAX_VEHICLES) {
        printf("The stand is full, please como back later\n");
        return;
    }
    printf("--- Car data ---\n");
    setCodeNewVehicle(vehicles, quantity);
    printf("Code: %d\n", vehicles[*quantity].code);
    readVehicleData(file, &vehicles[*quantity]);
    (*quantity)++;
}

static void editVehicle(FILE *file, vehicle *v) {
    if (v->isUnderContract) {
        printf("The vehicle is under a contract at the moment, please come back later\n");
        return;
    }
    printf("--- Vehicle data ---\n");
    readVehicleData(stdin, v);
}

static void deleteVehicle(vehicle *vehicles, const int position, size_t *qtd) {
    if (vehicles[position].isUnderContract) {
        printf("The vehicle is under a contract at the moment, please come back later\n");
        return;
    }
    for (int i = position; i <= *qtd; i++) {
        vehicles[i] = vehicles[i + 1];
    }
    (*qtd)--;
}

static void showVehicle(const vehicle v) {
    printf("Code: %d\n", v.code);
    printf("Brand: %s\n", v.brand);
    printf("Model: %s\n", v.model);
    printf("Registration plate: %s\n", v.registrationPlate);
    printf("Kms: %.2f\n", v.km);
    printf("Status: %s\n", v.isUnderContract ? "Unavailable" : "Available");
}

void manageVehicleByCode(FILE *file, vehicle *vehicles, size_t *quantity) {
    if (*quantity == 0) {
        printf("There are no registered vehicles\n");
        return;
    }
    const int n = readInt(file, 0, MAX_VEHICLES - 1);
    const int codeFound = searchCodeVehicle(vehicles, *quantity, n);
    if (codeFound >= 0) {
        showVehicle(vehicles[codeFound]);
        printf("Edit(e) Delete(d) (Press any other key plus enter to leave this menu)\n");
        unsigned char op;
        do {
            op = fgetc(file);
        } while (op == '\n');
        if (op == 'E' || op == 'e') {
            editVehicle(file, &vehicles[codeFound]);
        } else if (op == 'D' || op == 'd') {
            deleteVehicle(vehicles, codeFound, quantity);
            printf("Vehicle deleted successfully\n");
        }
    } else {
        printf("No vehicle found with code %d\n", n);
    }
}

void showAllVehicles(const vehicle *vehicles, const size_t quantity) {
    if (quantity == 0) {
        printf("There are no registered vehicles\n");
        return;
    }
    printf("--- Vehicle data ---\n\n");
    for (int i = 0; i < quantity; i++) {
        showVehicle(vehicles[i]);
        printf("\n");
    }
}

void showVehiclesLocation(const vehicle *vehicles, const size_t quantity) {
    if (quantity == 0) {
        printf("There are no registered vehicles\n");
        return;
    }
    printf("              |                             OFFICES                          |\n");
    printf("VEHICLES      |%s   |%s |%s  |%s    |%s  |%s   |%s |\n", officeEnumToText(Braga), officeEnumToText(Coimbra), officeEnumToText(Guarda), officeEnumToText(Faro), officeEnumToText(Lisbon), officeEnumToText(Porto), officeEnumToText(Unknown));
    printf("--------------|--------|--------|--------|--------|--------|--------|--------|\n");
    for (int i = 0; i < quantity; i++) {
        printf("%-5d", vehicles[i].code);
        printf("         |");
        for (int j = 0; j < MAX_OFFICES; j++) {
            char text[10] = "\0";
            strcat(text, "    \0");
            text[4] = j == vehicles[i].location ? 'x' : ' ';
            strcat(text, "   |\0");
            printf("%s", text);
        }
        printf("\n");
    }
}

void readVehicles(const char *fileName, vehicle *vehicles, size_t *quantity) {
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        printf("Error opening file '%s'!\n", fileName);
        return;
    }

    // calculate the number of vehicles
    fseek(file, 0, SEEK_END);
    *quantity = ftell(file) / sizeof(vehicle);

    // set the file position back to the beginning
    rewind(file);

    // check that the number of vehicles is not bigger than expected
    if (*quantity > MAX_VEHICLES) {
        printf("Error: invalid file size in '%s'\n", fileName);
        fclose(file);
        return;
    }

    // read the vehicles
    fread(vehicles, sizeof(vehicle), *quantity, file);

    fclose(file);
}

// function to write vehicles to a binary file
void writeVehicles(const char *fileName, const vehicle *vehicles, const size_t quantity) {
    FILE *file = fopen(fileName, "wb");
    if (file == NULL) {
        printf("Error opening file '%s'!\n", fileName);
        return;
    }

    // write the vehicles
    fwrite(vehicles, sizeof(vehicle), quantity, file);

    fclose(file);
}
