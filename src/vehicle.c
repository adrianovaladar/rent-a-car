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

static void readVehicleData(FILE *inputFile, FILE *outputFile, vehicle *v) {
    readString(inputFile, outputFile, v->brand, 11, "Brand (maximum 10 characters): ");
    readString(inputFile, outputFile, v->model, 11, "Model (maximum 10 characters): ");
    readString(inputFile, outputFile, v->registrationPlate, 7, "Registration plate (maximum 6 characters): ");
    v->isUnderContract = false;
    fprintf(outputFile, "Kms\n");
    v->km = readFloat(inputFile, outputFile, 0, INFINITY);
    fprintf(outputFile, "Office\n");
    fprintf(outputFile, "%s %d %s %d %s %d %s %d %s %d %s %d\n", officeEnumToText(Braga), Braga, officeEnumToText(Coimbra), Coimbra, officeEnumToText(Guarda), Guarda, officeEnumToText(Faro), Faro, officeEnumToText(Lisbon), Lisbon, officeEnumToText(Porto), Porto);
    v->location = readInt(inputFile, outputFile, 0, 5);
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

void insertVehicle(FILE *inputFile, FILE *outputFile, vehicle *vehicles, size_t *quantity) {
    if (*quantity == MAX_VEHICLES) {
        fprintf(outputFile, "The stand is full, please como back later\n");
        return;
    }
    fprintf(outputFile, "--- Car data ---\n");
    setCodeNewVehicle(vehicles, quantity);
    fprintf(outputFile, "Code: %d\n", vehicles[*quantity].code);
    readVehicleData(inputFile, outputFile,&vehicles[*quantity]);
    (*quantity)++;
}

static void editVehicle(FILE *inputFile, FILE *outputFile, vehicle *v) {
    if (v->isUnderContract) {
        fprintf(outputFile, "The vehicle is under a contract at the moment, please come back later\n");
        return;
    }
    fprintf(outputFile, "--- Vehicle data ---\n");
    readVehicleData(inputFile, outputFile,v);
}

static void deleteVehicle(FILE *outputFile, vehicle *vehicles, const int position, size_t *qtd) {
    if (vehicles[position].isUnderContract) {
        fprintf(outputFile, "The vehicle is under a contract at the moment, please come back later\n");
        return;
    }
    for (int i = position; i < *qtd; i++) {
        vehicles[i] = vehicles[i + 1];
    }
    (*qtd)--;
}

static void showVehicle(FILE *outputFile, const vehicle v) {
    fprintf(outputFile, "Code: %d\n", v.code);
    fprintf(outputFile, "Brand: %s\n", v.brand);
    fprintf(outputFile, "Model: %s\n", v.model);
    fprintf(outputFile, "Registration plate: %s\n", v.registrationPlate);
    fprintf(outputFile, "Kms: %.2f\n", v.km);
    fprintf(outputFile, "Status: %s\n", v.isUnderContract ? "Unavailable" : "Available");
}

void manageVehicleByCode(FILE *inputFile, FILE *outputFile, vehicle *vehicles, size_t *quantity) {
    if (*quantity == 0) {
        fprintf(outputFile, "There are no registered vehicles\n");
        return;
    }
    const int n = readInt(inputFile, outputFile, 0, MAX_VEHICLES - 1);
    const int codeFound = searchCodeVehicle(vehicles, *quantity, n);
    if (codeFound >= 0) {
        showVehicle(outputFile, vehicles[codeFound]);
        fprintf(outputFile, "Edit(e) Delete(d) (Press any other key plus enter to leave this menu)\n");
        unsigned char op;
        do {
            op = fgetc(inputFile);
        } while (op == '\n');
        if (op == 'E' || op == 'e') {
            editVehicle(inputFile, outputFile, &vehicles[codeFound]);
        } else if (op == 'D' || op == 'd') {
            deleteVehicle(outputFile, vehicles, codeFound, quantity);
            fprintf(outputFile, "Vehicle deleted successfully\n");
        }
    } else {
        fprintf(outputFile, "No vehicle found with code %d\n", n);
    }
}

void showAllVehicles(FILE *outputFile, const vehicle *vehicles, const size_t quantity) {
    if (quantity == 0) {
        fprintf(outputFile, "There are no registered vehicles\n");
        return;
    }
    fprintf(outputFile, "--- Vehicle data ---\n\n");
    for (int i = 0; i < quantity; i++) {
        showVehicle(outputFile, vehicles[i]);
        fprintf(outputFile, "\n");
    }
}

void showVehiclesLocation(FILE *outputFile, const vehicle *vehicles, const size_t quantity) {
    if (quantity == 0) {
        fprintf(outputFile, "There are no registered vehicles\n");
        return;
    }
    fprintf(outputFile, "              |                             OFFICES                          |\n");
    fprintf(outputFile, "VEHICLES      |%s   |%s |%s  |%s    |%s  |%s   |%s |\n", officeEnumToText(Braga), officeEnumToText(Coimbra), officeEnumToText(Guarda), officeEnumToText(Faro), officeEnumToText(Lisbon), officeEnumToText(Porto), officeEnumToText(Unknown));
    fprintf(outputFile, "--------------|--------|--------|--------|--------|--------|--------|--------|\n");
    for (int i = 0; i < quantity; i++) {
        fprintf(outputFile, "%-5d", vehicles[i].code);
        fprintf(outputFile, "         |");
        for (int j = 0; j < MAX_OFFICES; j++) {
            char text[10] = "\0";
            strcat(text, "    \0");
            text[4] = j == vehicles[i].location ? 'x' : ' ';
            strcat(text, "   |\0");
            fprintf(outputFile, "%s", text);
        }
        fprintf(outputFile, "\n");
    }
}

void readVehicles(FILE *outputFile, const char *fileName, vehicle *vehicles, size_t *quantity) {
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        fprintf(outputFile, "Error opening file '%s'!\n", fileName);
        return;
    }

    // calculate the number of vehicles
    fseek(file, 0, SEEK_END);
    *quantity = ftell(file) / sizeof(vehicle);

    // set the file position back to the beginning
    rewind(file);

    // check that the number of vehicles is not bigger than expected
    if (*quantity > MAX_VEHICLES) {
        fprintf(outputFile, "Error: invalid file size in '%s'\n", fileName);
        fclose(file);
        return;
    }

    // read the vehicles
    fread(vehicles, sizeof(vehicle), *quantity, file);

    fclose(file);
}

// function to write vehicles to a binary file
void writeVehicles(FILE *outputFile, const char *fileName, const vehicle *vehicles, const size_t quantity) {
    FILE *file = fopen(fileName, "wb");
    if (file == NULL) {
        fprintf(outputFile, "Error opening file '%s'!\n", fileName);
        return;
    }

    // write the vehicles
    fwrite(vehicles, sizeof(vehicle), quantity, file);

    fclose(file);
}
