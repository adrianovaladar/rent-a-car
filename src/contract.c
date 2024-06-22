#include "contract.h"
#include "input.h"
#include "vehicle.h"
#include <math.h>
#include <stdio.h>

static void showContract(contract c) {
    printf("Customer Code: %d\n", c.codeCustomer);
    printf("Vehicle code: %d\n", c.codeVehicle);
    printf("Price per day: %.2f\n", c.priceDay);
    printf("Start date: %d/%d/%d\n", c.startDate.day, c.startDate.month, c.startDate.year);
    printf("Start office: %s\n", officeEnumToText(c.startOffice));
    if (!isEmptyDate(c.endDate)) {
        printf("End date: %d/%d/%d\n", c.endDate.day, c.endDate.month, c.endDate.year);
        printf("End office: %s\n", officeEnumToText(c.endOffice));
        printf("Quantity kms: %.2f\n", c.quantityKm);
        printf("Price: %.2f\n", c.price);
    }
    printf("Note: date format is dd/mm/yyyy\n");
}

void showContracts(contract c[], size_t quantity) {
    if (quantity == 0) {
        printf("There are no registered contracts\n");
        return;
    }
    char value;
    printf("--- Contract data ---\n\n");
    for (int i = 0; i < quantity; i++) {
        showContract(c[i]);
        printf("\n");
    }
    if (quantity > 1) {
        printf("Sort by start date? Yes(y) No(n): ");
        do {
            scanf("%c", &value);
        } while (value != 'n' && value != 'N' && value != 'y' && value != 'Y');
        if (value == 'y' || value == 'Y') {
            contract tmp;
            contract copyContracts[quantity];
            for (int i = 0; i < quantity; i++) {
                copyContracts[i] = c[i];
            }
            for (int j = 1; j < quantity; j++) {
                for (int i = 0; i < quantity - 1; i++) {
                    if (isDateAfter(copyContracts[i].startDate, copyContracts[i + 1].startDate)) {
                        tmp = copyContracts[i];
                        copyContracts[i] = copyContracts[i + 1];
                        copyContracts[i + 1] = tmp;
                    }
                }
            }
            printf("\n");
            printf("--- Contract data ---\n\n");
            for (int i = 0; i < quantity; i++) {
                showContract(copyContracts[i]);
                printf("\n");
            }
        }
    }
}

static void editContract(contract contracts[], int pos, size_t quantity) {
    if (contracts[pos].endDate.year != 0) {
        printf("Not possible to edit this contract because it is already closed\n");
        return;
    }
    printf("Insert the price per day\n");
    contracts[pos].priceDay = readFloat(stdin, 0.01f, 9999);
    bool isLegalDate;
    do {
        isLegalDate = true;
        readDate(stdin, &contracts[pos].startDate);
        for (int i = 0; i < quantity && isLegalDate != false; i++) {
            if (contracts[pos].codeVehicle == contracts[i].codeVehicle && isDateWithinRange(contracts[i].startDate, contracts[i].endDate, contracts[quantity].startDate)) {
                printf("The vehicle was unavailable for the intended date. It was under other contract\n");
                isLegalDate = false;
            }
        }
    } while (!isLegalDate);
}

static void deleteContract(contract c[], int pos, size_t *quantity, vehicle vehicles[], customer customers[], size_t quantityVehicles, size_t quantityCustomers) {
    if (c[pos].endDate.day == 0)
        printf("Not possible to delete this contract because it is still ongoing\n");
    else {
        int i;
        for (i = pos; i <= *quantity; i++) {
            c[i] = c[i + 1];
        }
        int customerPosition = searchCodeCustomer(customers, quantityCustomers, c[pos].codeCustomer);
        customers[customerPosition].isUnderContract = false;
        int vehiclePosition = searchCodeVehicle(vehicles, quantityVehicles, c[pos].codeVehicle);
        vehicles[vehiclePosition].isUnderContract = false;
        (*quantity)--;
    }
}

static int searchByStartingDate(contract cont[], size_t quantity) {
    int i, position = -1;
    date date;
    readDate(stdin, &date);
    for (i = 0; i <= quantity; i++)
        if (areDatesEqual(cont[i].startDate, date))
            position = i;
    return position;
}

static int searchContract(contract c[], size_t quantityContracts) {
    int aux = -1;
    int position, insertedCodeValue;
    printf("Contract start date\n");
    position = searchByStartingDate(c, quantityContracts);
    printf("Vehicle code\n");
    insertedCodeValue = readInt(stdin, 0, MAX_VEHICLES - 1);
    if (insertedCodeValue == c[position].codeVehicle)
        aux = position;
    return aux;
}

void startContract(contract contracts[], customer customers[], vehicle vehicles[], size_t quantityCustomers, size_t quantityVehicles, size_t *quantityContracts) {
    if (*quantityContracts == MAX_CONTRACTS) {
        printf("We reached our full capacity of contracts. Please come back later");
        return;
    }
    int n, positionCustomer, positionVehicle, i;
    if (quantityVehicles == 0 || quantityCustomers == 0)
        printf("There are no registered clients or vehicles so a contract cannot be started\n");
    else {
        do {
            printf("Customer code\n");
            n = readInt(stdin, 0, MAX_CUSTOMERS - 1);
            positionCustomer = searchCodeCustomer(customers, quantityCustomers, n);
            if (positionCustomer < 0) {
                printf("Customer not found, try another code\n");
            }
        } while (positionCustomer < 0);
        if (customers[positionCustomer].isRisky == 1) {
            printf("This is a risky client so we cannot proceed with the contract\n");
            return;
        }
        do {
            printf("Vehicle code\n");
            n = readInt(stdin, 0, MAX_VEHICLES - 1);
            positionVehicle = searchCodeVehicle(vehicles, quantityVehicles, n);
            if (positionVehicle < 0) {
                printf("Vehicle not found, try another code\n");
            }
        } while (positionVehicle < 0);
        if (vehicles[positionVehicle].isUnderContract == true) {
            printf("The vehicle is unavailable, not possible to proceed\n");
            return;
        }
        customers[positionCustomer].isUnderContract = true;
        contracts[*quantityContracts].codeCustomer = customers[positionCustomer].code;
        vehicles[positionVehicle].isUnderContract = true;
        contracts[*quantityContracts].codeVehicle = vehicles[positionVehicle].code;
        printf("Price per day\n");
        contracts[*quantityContracts].priceDay = readFloat(stdin, 0.01f, 9999.0f);
        bool isLegalDate;
        printf("Start date\n");
        do {
            isLegalDate = true;
            readDate(stdin, &contracts[*quantityContracts].startDate);
            for (i = 0; i < *quantityContracts && isLegalDate != false; i++) {
                if (contracts[*quantityContracts].codeVehicle == contracts[i].codeVehicle && isDateWithinRange(contracts[i].startDate, contracts[i].endDate, contracts[*quantityContracts].startDate)) {
                    printf("The vehicle was unavailable for the intended date. It was under other contract\n");
                    isLegalDate = false;
                }
            }
        } while (!isLegalDate);
        printf("Information: This vehicle is in %s, this will be considered for the start office of the contract\n", officeEnumToText(vehicles[positionVehicle].location));
        contracts[*quantityContracts].startOffice = vehicles[positionVehicle].location;
        vehicles[positionVehicle].location = Unknown;
        (*quantityContracts)++;
    }
}


static void endContract(contract contracts[], int pos, vehicle vehicles[], customer customers[], size_t quantityCustomers, size_t quantityVehicles, size_t quantityContracts) {
    if (contracts[pos].endDate.day != 0)
        printf("Not possible to end this contract because it is already closed\n");
    else {
        char value;
        int i, positionCustomer, positionVehicle;
        printf("Is the vehicle in a good status? Yes(y) No(n) ");
        do {
            scanf("%c", &value);
        } while (value != 'y' && value != 'Y' && value != 'n' && value != 'N');
        positionCustomer = searchCodeCustomer(customers, quantityCustomers, contracts[pos].codeCustomer);
        if (value == 'n' || value == 'N') {
            customers[positionCustomer].isRisky = 1;
        }
        customers[positionCustomer].isUnderContract = false;
        positionVehicle = searchCodeVehicle(vehicles, quantityVehicles, contracts[pos].codeVehicle);
        vehicles[positionVehicle].isUnderContract = false;
        printf("Quantity of km\n");
        contracts[pos].quantityKm = readFloat(stdin, vehicles[positionVehicle].km, INFINITY);
        vehicles[positionVehicle].km += contracts[pos].quantityKm;
        bool isLegalDate = true;
        printf("End date\n");
        do {
            isLegalDate = true;
            readDate(stdin, &contracts[pos].endDate);
            if (isDateBefore(contracts[pos].startDate, contracts[pos].endDate)) {
                printf("End date cannot be less than start date\n");
                printf("Start date: %d/%d/%d\n", contracts[pos].startDate.day, contracts[pos].startDate.month, contracts[pos].startDate.year);
                isLegalDate = false;
            }
            for (i = 0; i < quantityContracts && isLegalDate != false; i++) {
                if (i == pos) {
                    continue;
                }
                if (contracts[pos].codeVehicle == contracts[i].codeVehicle && isDateWithinRange(contracts[i].startDate, contracts[i].endDate, contracts[pos].endDate)) {
                    printf("The vehicle was unavailable for the intended date. It was under other contract\n");
                    isLegalDate = false;
                }
            }
        } while (!isLegalDate);
        contracts[pos].price = (float) (diffInDays(contracts[pos].startDate, contracts[pos].endDate) + 1) * contracts[pos].priceDay;
        printf("Office where the vehicle is:\n");
        printf("%s %d %s %d %s %d %s %d %s %d %s %d", officeEnumToText(Braga), Braga, officeEnumToText(Coimbra), Coimbra, officeEnumToText(Guarda), Guarda, officeEnumToText(Faro), Faro, officeEnumToText(Lisbon), Lisbon, officeEnumToText(Porto), Porto);
        contracts[pos].endOffice = readInt(stdin, 0, 5);
        vehicles[positionVehicle].location = contracts[pos].endOffice;
    }
}

void showContractByVehicleCodeAndStartDateAndShowOptions(contract contracts[], vehicle vehicles[], customer customers[], size_t *quantityContracts, size_t quantityVehicles, size_t quantityCustomers) {
    int contractPosition;
    if (*quantityContracts == 0) {
        printf("There are no registered contracts\n");
        return;
    }
    contractPosition = searchContract(contracts, *quantityContracts);
    if (contractPosition >= 0) {
        showContract(contracts[contractPosition]);
        printf("Edit(e) Delete(d) End (t) (Press any other key plus enter to leave this menu)\n");
        unsigned char op;
        do {
            op = getchar();
        } while (op == '\n');
        if (op == 'T' || op == 't') {
            endContract(contracts, contractPosition, vehicles, customers, quantityCustomers, quantityVehicles, *quantityContracts);
        } else if (op == 'E' || op == 'e') {
            editContract(contracts, contractPosition, *quantityContracts);
        } else if (op == 'D' || op == 'd') {
            deleteContract(contracts, contractPosition, quantityContracts, vehicles, customers, quantityVehicles, quantityCustomers);
            printf("Contract deleted successfully\n");
        }
    } else {
        printf("No contract found with data provided\n");
    }
}

void readContracts(char *fileName, contract contracts[], size_t *quantity) {
    FILE *file;
    file = fopen(fileName, "rb");
    if (file == NULL) {
        printf("Error opening file '%s'!\n", fileName);
        return;
    }

    // calculate the number of contracts
    fseek(file, 0, SEEK_END);
    *quantity = ftell(file) / sizeof(contract);

    // set the file position back to the beginning
    rewind(file);

    // check that the number of contracts is not negative or bigger than expected
    if (*quantity < 0 || *quantity > MAX_CONTRACTS) {
        printf("Error: invalid file size in '%s'\n", fileName);
        fclose(file);
        return;
    }

    // read the contracts
    fread(contracts, sizeof(contract), *quantity, file);

    fclose(file);
}

// function to write contracts to a binary file
void writeContracts(char *fileName, contract contracts[], size_t quantity) {
    FILE *file;
    file = fopen(fileName, "wb");
    if (file == NULL) {
        printf("Error opening file '%s'!\n", fileName);
        return;
    }

    // write the contracts
    fwrite(contracts, sizeof(contract), quantity, file);

    fclose(file);
}
