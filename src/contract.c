#include "contract.h"
#include "input.h"
#include "vehicle.h"
#include "constants.h"
#include <math.h>
#include <stdio.h>

static void showContract(FILE *outputFile, const contract c) {
    fprintf(outputFile, "Customer Code: %d\n", c.codeCustomer);
    fprintf(outputFile, "Vehicle code: %d\n", c.codeVehicle);
    fprintf(outputFile, "Price per day: %.2f\n", c.priceDay);
    fprintf(outputFile, "Start date: %d/%d/%d\n", c.startDate.day, c.startDate.month, c.startDate.year);
    fprintf(outputFile, "Start office: %s\n", officeEnumToText(c.startOffice));
    if (!isEmptyDate(c.endDate)) {
        fprintf(outputFile, "End date: %d/%d/%d\n", c.endDate.day, c.endDate.month, c.endDate.year);
        fprintf(outputFile, "End office: %s\n", officeEnumToText(c.endOffice));
        fprintf(outputFile, "Quantity kms: %.2f\n", c.quantityKm);
        fprintf(outputFile, "Price: %.2f\n", c.price);
    }
    fprintf(outputFile, "Note: date format is dd/mm/yyyy\n");
}

static void showSortedContractsByStartDate(FILE *outputFile, const contract *contracts, const size_t quantity) {
    contract copyContracts[quantity];
    for (int i = 0; i < quantity; i++) {
        copyContracts[i] = contracts[i];
    }
    for (int j = 1; j < quantity; j++) {
        for (int i = 0; i < quantity - 1; i++) {
            if (isDateAfter(copyContracts[i].startDate, copyContracts[i + 1].startDate)) {
                const contract tmp = copyContracts[i];
                copyContracts[i] = copyContracts[i + 1];
                copyContracts[i + 1] = tmp;
            }
        }
    }
    fprintf(outputFile, "\n");
    fprintf(outputFile, "--- Contract data ---\n\n");
    for (int i = 0; i < quantity; i++) {
        showContract(outputFile, copyContracts[i]);
        fprintf(outputFile, "\n");
    }
}

void showContracts(FILE *outputFile, const contract *contracts, const size_t quantity) {
    if (quantity == 0) {
        fprintf(outputFile, "There are no registered contracts\n");
        return;
    }
    char value;
    fprintf(outputFile, "--- Contract data ---\n\n");
    for (int i = 0; i < quantity; i++) {
        showContract(outputFile, contracts[i]);
        fprintf(outputFile, "\n");
    }
    if (quantity > 1) {
        fprintf(outputFile, "Sort by start date? Yes(y) No(n): ");
        do {
            scanf("%c", &value);
        } while (value != 'n' && value != 'N' && value != 'y' && value != 'Y');
        if (value == 'y' || value == 'Y') {
            showSortedContractsByStartDate(outputFile, contracts, quantity);
        }
    }
}

static void editContract(FILE *inputFile, FILE *outputFile, const logger *logger, contract *contracts, const int pos, const size_t quantity) {
    if (contracts[pos].endDate.year != 0) {
        fprintf(outputFile, "Not possible to edit this contract because it is already closed\n");
        logFormattedMessage(logger, Warning, __FILE__, __FUNCTION__, __LINE__, "Failed to edit contract for vehicle code %d and start date %s", contracts[pos].codeVehicle, getFormattedDate(contracts[pos].startDate));
        return;
    }
    fprintf(outputFile, "Insert the price per day\n");
    contracts[pos].priceDay = readFloat(inputFile, outputFile, 0.01f, 9999);
    bool isLegalDate;
    do {
        isLegalDate = true;
        readDate(inputFile, outputFile, &contracts[pos].startDate);
        for (int i = 0; i < quantity; i++) {
            if (contracts[pos].codeVehicle == contracts[i].codeVehicle && isDateWithinRange(contracts[i].startDate, contracts[i].endDate, contracts[quantity].startDate)) {
                fprintf(outputFile, "The vehicle was unavailable for the intended date. It was under other contract\n");
                isLegalDate = false;
                break;
            }
        }
    } while (!isLegalDate);
    logFormattedMessage(logger, Info, __FILE__, __FUNCTION__, __LINE__, "Contract edited: price per day '%.2f' start date '%s'", contracts[pos].priceDay, getFormattedDate(contracts[pos].startDate));
}

static void deleteContract(FILE *outputFile, const logger *logger, contract *c, const int pos, size_t *quantity, vehicle *vehicles, const size_t quantityVehicles, customer *customers, const size_t quantityCustomers) {
    if (c[pos].endDate.day == 0) {
        fprintf(outputFile, "Not possible to delete this contract because it is still ongoing\n");
        logFormattedMessage(logger, Warning, __FILE__, __FUNCTION__, __LINE__, "Failed to edit contract for vehicle code %d and start date %s", c->codeVehicle, getFormattedDate(c->startDate));
        return;
    }
    const int code = c->codeVehicle;
    char *date = getFormattedDate(c->startDate);
    for (int i = pos; i < *quantity; i++) {
        c[i] = c[i + 1];
    }
    const int customerPosition = searchCodeCustomer(logger, customers, quantityCustomers, c[pos].codeCustomer);
    customers[customerPosition].isUnderContract = false;
    const int vehiclePosition = searchCodeVehicle(logger, vehicles, quantityVehicles, c[pos].codeVehicle);
    vehicles[vehiclePosition].isUnderContract = false;
    (*quantity)--;
    fprintf(outputFile, "Contract deleted successfully\n");
    logFormattedMessage(logger, Info, __FILE__, __FUNCTION__, __LINE__, "Contract with vehicle code %d and start date %s deleted successfully", code, date);
}

static int searchByStartingDate(FILE *inputFile, FILE *outputFile, const logger *logger, const contract *c, const size_t quantity, const int codeVehicle) {
    int position = -1;
    date date;
    readDate(inputFile, outputFile, &date);
    for (int i = 0; i <= quantity; i++) {
        if (areDatesEqual(c[i].startDate, date) && codeVehicle == c[i].codeVehicle) {
            position = i;
            break;
        }
    }
    if (position == -1) {
        logFormattedMessage(logger, Info, __FILE__, __FUNCTION__, __LINE__, "Contract with vehicle code %d and start date %s not found", c->codeVehicle, getFormattedDate(c->startDate));
    } else {
        logFormattedMessage(logger, Info, __FILE__, __FUNCTION__, __LINE__, "Contract with vehicle code %d and start date %s found", c->codeVehicle, getFormattedDate(c->startDate));
    }
    return position;
}

static int searchContract(FILE *inputFile, FILE *outputFile, const logger *logger, const contract *contracts, const size_t quantityContracts) {
    fprintf(outputFile, "Vehicle code\n");
    const int vehicleCode = readInt(inputFile, outputFile, 0, MAX_VEHICLES - 1);
    fprintf(outputFile, "Contract start date\n");
    return searchByStartingDate(inputFile, outputFile, logger, contracts, quantityContracts, vehicleCode);
}

void startContract(FILE *inputFile, FILE *outputFile, const logger *logger, contract *contracts, customer *customers, vehicle *vehicles, size_t *quantityContracts, const size_t quantityCustomers, const size_t quantityVehicles) {
    if (*quantityContracts == MAX_CONTRACTS) {
        fprintf(outputFile, "We reached our full capacity of contracts. Please come back later");
        logFormattedMessage(logger, Warning, __FILE__, __FUNCTION__, __LINE__, "Failed to insert contract: maximum capacity reached", Warning, __FILE__, __FUNCTION__, __LINE__);
        return;
    }
    if (quantityVehicles == 0 || quantityCustomers == 0) {
        fprintf(outputFile, "There are no registered clients or vehicles so a contract cannot be started\n");
        logFormattedMessage(logger, Warning, __FILE__, __FUNCTION__, __LINE__, "Failed to insert contract: no registered clients or vehicles", Warning, __FILE__, __FUNCTION__, __LINE__);
        return;
    }
    int n;
    int positionCustomer;
    int positionVehicle;
    do {
        fprintf(outputFile, "Customer code\n");
        n = readInt(inputFile, outputFile, 0, MAX_CUSTOMERS - 1);
        positionCustomer = searchCodeCustomer(logger, customers, quantityCustomers, n);
        if (positionCustomer < 0) {
            fprintf(outputFile, "Customer not found, try another code\n");
        }
    } while (positionCustomer < 0);
    if (customers[positionCustomer].isRisky == 1) {
        fprintf(outputFile, "This is a risky client so we cannot proceed with the contract\n");
        logFormattedMessage(logger, Warning, __FILE__, __FUNCTION__, __LINE__, "Failed to insert contract: customer with code %d is risky", customers[positionCustomer]);
        return;
    }
    do {
        fprintf(outputFile, "Vehicle code\n");
        n = readInt(inputFile, outputFile, 0, MAX_VEHICLES - 1);
        positionVehicle = searchCodeVehicle(logger, vehicles, quantityVehicles, n);
        if (positionVehicle < 0) {
            fprintf(outputFile, "Vehicle not found, try another code\n");
        }
    } while (positionVehicle < 0);
    if (vehicles[positionVehicle].isUnderContract == true) {
        fprintf(outputFile, "The vehicle is unavailable, not possible to proceed\n");
        logFormattedMessage(logger, Warning, __FILE__, __FUNCTION__, __LINE__, "Failed to insert contract: vehicle with code %d is unavailable", vehicles[positionVehicle]);
        return;
    }
    customers[positionCustomer].isUnderContract = true;
    contracts[*quantityContracts].codeCustomer = customers[positionCustomer].code;
    vehicles[positionVehicle].isUnderContract = true;
    contracts[*quantityContracts].codeVehicle = vehicles[positionVehicle].code;
    fprintf(outputFile, "Price per day\n");
    contracts[*quantityContracts].priceDay = readFloat(inputFile, outputFile, 0.01f, 9999.0f);
    bool isLegalDate;
    fprintf(outputFile, "Start date\n");
    do {
        isLegalDate = true;
        readDate(inputFile, outputFile, &contracts[*quantityContracts].startDate);
        for (int i = 0; i < *quantityContracts; i++) {
            if (contracts[*quantityContracts].codeVehicle == contracts[i].codeVehicle && isDateWithinRange(contracts[i].startDate, contracts[i].endDate, contracts[*quantityContracts].startDate)) {
                fprintf(outputFile, "The vehicle was unavailable for the intended date. It was under other contract\n");
                isLegalDate = false;
                break;
            }
        }
    } while (!isLegalDate);
    fprintf(outputFile, "Information: This vehicle is in %s, this will be considered for the start office of the contract\n", officeEnumToText(vehicles[positionVehicle].location));
    contracts[*quantityContracts].startOffice = vehicles[positionVehicle].location;
    vehicles[positionVehicle].location = Unknown;
    logFormattedMessage(logger, Info, __FILE__, __FUNCTION__, __LINE__, "Contract added: customer code %d vehicle code '%d' start date '%s' price per day '%d'", contracts[*quantityContracts].codeCustomer, contracts[*quantityContracts].codeVehicle, getFormattedDate(contracts[*quantityContracts].startDate), contracts[*quantityContracts].priceDay);
    (*quantityContracts)++;
}

static void endContract(FILE *inputFile, FILE *outputFile, const logger *logger, contract *contracts, const int pos, vehicle *vehicles, customer *customers, const size_t quantityCustomers, const size_t quantityVehicles, const size_t quantityContracts) {
    if (contracts[pos].endDate.day != 0) {
        fprintf(outputFile, "Not possible to end this contract because it is already closed\n");
        logFormattedMessage(logger, Warning, __FILE__, __FUNCTION__, __LINE__, "Failed to end contract: already closed", Warning, __FILE__, __FUNCTION__, __LINE__);
        return;
    }
    char value;
    fprintf(outputFile, "Is the vehicle in a good status? Yes(y) No(n) ");
    do {
        fscanf(inputFile, "%c", &value);
    } while (value != 'y' && value != 'Y' && value != 'n' && value != 'N');
    const int positionCustomer = searchCodeCustomer(logger, customers, quantityCustomers, contracts[pos].codeCustomer);
    if (value == 'n' || value == 'N') {
        customers[positionCustomer].isRisky = true;
    }
    customers[positionCustomer].isUnderContract = false;
    const int positionVehicle = searchCodeVehicle(logger, vehicles, quantityVehicles, contracts[pos].codeVehicle);
    vehicles[positionVehicle].isUnderContract = false;
    fprintf(outputFile, "Quantity of km\n");
    contracts[pos].quantityKm = readFloat(inputFile, outputFile, vehicles[positionVehicle].km, INFINITY);
    vehicles[positionVehicle].km += contracts[pos].quantityKm;
    bool isLegalDate = true;
    fprintf(outputFile, "End date\n");
    do {
        isLegalDate = true;
        readDate(inputFile, outputFile, &contracts[pos].endDate);
        if (isDateBefore(contracts[pos].endDate, contracts[pos].startDate)) {
            fprintf(outputFile, "End date cannot be less than start date\n");
            fprintf(outputFile, "Start date: %d/%d/%d\n", contracts[pos].startDate.day, contracts[pos].startDate.month, contracts[pos].startDate.year);
            isLegalDate = false;
        }
        for (int i = 0; i < quantityContracts; i++) {
            if (i == pos) {
                continue;
            }
            if (contracts[pos].codeVehicle == contracts[i].codeVehicle && isDateWithinRange(contracts[i].startDate, contracts[i].endDate, contracts[pos].endDate)) {
                fprintf(outputFile, "The vehicle was unavailable for the intended date. It was under other contract\n");
                isLegalDate = false;
                break;
            }
        }
    } while (!isLegalDate);
    contracts[pos].price = (float) (diffInDays(contracts[pos].startDate, contracts[pos].endDate) + 1) * contracts[pos].priceDay;
    fprintf(outputFile, "Office where the vehicle is:\n");
    fprintf(outputFile, "%s %d %s %d %s %d %s %d %s %d %s %d\n", officeEnumToText(Braga), Braga, officeEnumToText(Coimbra), Coimbra, officeEnumToText(Guarda), Guarda, officeEnumToText(Faro), Faro, officeEnumToText(Lisbon), Lisbon, officeEnumToText(Porto), Porto);
    contracts[pos].endOffice = readInt(inputFile, outputFile, 0, 5);
    vehicles[positionVehicle].location = contracts[pos].endOffice;
    logFormattedMessage(logger, Info, __FILE__, __FUNCTION__, __LINE__, "Contract ended: customer code %d vehicle code '%d' start date '%s' end date '%s' price per day '%f' final price %f", contracts[quantityContracts].codeCustomer, contracts[quantityContracts].codeVehicle, getFormattedDate(contracts[quantityContracts].startDate), getFormattedDate(contracts[quantityContracts].endDate), contracts[quantityContracts].priceDay, contracts[quantityContracts].price);
}

void manageContractByVehicleCodeAndStartDate(FILE *inputFile, FILE *outputFile, const logger *logger, contract *contracts, vehicle *vehicles, customer *customers, size_t *quantityContracts, const size_t quantityVehicles, const size_t quantityCustomers) {
    if (*quantityContracts == 0) {
        fprintf(outputFile, "There are no registered contracts\n");
        return;
    }
    const int contractPosition = searchContract(inputFile, outputFile, logger, contracts, *quantityContracts);
    if (contractPosition >= 0) {
        showContract(outputFile, contracts[contractPosition]);
        fprintf(outputFile, "Edit(e) Delete(d) End (t) (Press any other key plus enter to leave this menu)\n");
        unsigned char op = 0;
        do {
            const int result = fgetc(inputFile);
            if (result == EOF) {
                continue;
            }
            op = (unsigned char) result;
        } while (op == '\n');
        if (op == 'T' || op == 't') {
            endContract(inputFile, outputFile, logger, contracts, contractPosition, vehicles, customers, quantityCustomers, quantityVehicles, *quantityContracts);
        } else if (op == 'E' || op == 'e') {
            editContract(inputFile, outputFile, logger, contracts, contractPosition, *quantityContracts);
        } else if (op == 'D' || op == 'd') {
            deleteContract(outputFile, logger, contracts, contractPosition, quantityContracts, vehicles, quantityVehicles, customers, quantityCustomers);
        }
    } else {
        fprintf(outputFile, "No contract found with data provided\n");
    }
}

void readContracts(FILE *outputFile, const logger *logger, const char *fileName, contract *contracts, size_t *quantity) {
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        fprintf(outputFile, "Error opening file '%s'!\n", fileName);
        logFormattedMessage(logger, Error, __FILE__, __FUNCTION__, __LINE__, "Cannot open file '%s'", fileName);
        return;
    }

    // calculate the number of contracts
    fseek(file, 0, SEEK_END);
    *quantity = ftell(file) / sizeof(contract);

    // set the file position back to the beginning
    rewind(file);

    // check that the number of contracts is not bigger than expected
    if (*quantity > MAX_CONTRACTS) {
        fprintf(outputFile, "Error: invalid file size in '%s'\n", fileName);
        logFormattedMessage(logger, Error, __FILE__, __FUNCTION__, __LINE__, "Invalid file size in '%s'", fileName);
        fclose(file);
        return;
    }

    // read the contracts
    fread(contracts, sizeof(contract), *quantity, file);
    fclose(file);
    logFormattedMessage(logger, Info, __FILE__, __FUNCTION__, __LINE__, "Successfully read %zu contracts from file '%s'", *quantity, fileName);
}

// function to write contracts to a binary file
void writeContracts(FILE *outputFile, const logger *logger, const char *fileName, const contract *contracts, const size_t quantity) {
    FILE *file = fopen(fileName, "wb");
    if (file == NULL) {
        fprintf(outputFile, "Error opening file '%s'!\n", fileName);
        logFormattedMessage(logger, Error, __FILE__, __FUNCTION__, __LINE__, "Cannot open file '%s'", fileName);
        return;
    }

    // write the contracts
    fwrite(contracts, sizeof(contract), quantity, file);
    fclose(file);
    logFormattedMessage(logger, Info, __FILE__, __FUNCTION__, __LINE__, "Successfully wrote %zu contracts to file '%s'", quantity, fileName);
}
