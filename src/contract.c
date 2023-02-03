#include "contract.h"
#include "input.h"
#include "vehicle.h"
#include <math.h>
#include <stdio.h>


static void showContract(contract c) {
    printf("\n--- Contract data ---\n");
    printf("Customer Code: %d\n", c.codeCustomer);
    printf("Vehicle code: %d\n", c.codeVehicle);
    printf("Price by day: %.2f\n", c.priceDay);
    printf("Start date: %d/%d/%d\n", c.startDate.day, c.startDate.month, c.startDate.year);
    printf("Start office: %s\n", officeEnumToText(c.startOffice));
    if (!isEmptyDate(c.endDate)) {
        printf("End date: %d/%d/%d\n", c.endDate.day, c.endDate.month, c.endDate.year);
        printf("End office: %s\n", officeEnumToText(c.startOffice));
        printf("Quantity kms: %.2f\n", c.quantityKm);
    }
    printf("Note: date format is dd/mm/yyyy\n");
}

void showContracts(contract c[], size_t quantity) {
    int i, j;
    char valor;
    if (quantity == 0) {
        printf("There are no registered contracts\n");
    } else {
        for (i = 0; i < quantity; i++) {
            showContract(c[i]);
        }
        if (quantity > 1) {
            printf("\nSort by date? Yes(y) No(n): ");
            scanf("%c", &valor);
            while (valor != 'n' && valor != 'N' && valor != 'y' && valor != 'Y') {
                scanf("%c", &valor);
            }
            if (valor == 'y' || valor == 'Y') {
                contract tmp;
                for (j = 1; j < quantity; j++) {
                    for (i = 0; i < quantity - 1; i++) {
                        if ((c[i].startDate.day > c[i + 1].startDate.day && c[i].startDate.month == c[i + 1].startDate.month && c[i].startDate.year == c[i + 1].startDate.year) || (c[i].startDate.month > c[i + 1].startDate.month && c[i].startDate.year == c[i + 1].startDate.year) || (c[i].startDate.year > c[i + 1].startDate.year)) {
                            tmp = c[i];
                            c[i] = c[i + 1];
                            c[i + 1] = tmp;
                        }
                    }
                }
                for (i = 0; i < quantity; i++) {
                    showContract(c[i]);
                }
            }
        }
    }
}

static void editContract(contract contracts[], vehicle vehicles[], int pos, size_t quantityVehicles, size_t quantity) {
    if (contracts[pos].endDate.year != 0) {
        printf("Not possible to edit this contract because it is already closed\n");
        return;
    }
    int vehiclePosition;
    vehiclePosition = searchCodeVehicle(vehicles, quantityVehicles, contracts[pos].codeVehicle);
    printf("Insert the price per day\n");
    contracts[pos].priceDay = readFloat(0.01f, 9999);
    date d;
    validateDate(&d);
    contracts[pos].startDate = d;
    for (int i = 0; i < quantity; i++) {
        while ((contracts[pos].codeVehicle == contracts[i].codeVehicle && contracts[pos].startDate.day >= contracts[i].startDate.day && contracts[pos].startDate.day < contracts[pos].endDate.day && contracts[pos].startDate.month == contracts[i].startDate.month && contracts[pos].startDate.month == contracts[i].endDate.month && contracts[pos].startDate.year == contracts[i].startDate.year && contracts[pos].startDate.year == contracts[i].endDate.year) || (contracts[pos].codeVehicle == contracts[i].codeVehicle && contracts[pos].startDate.month >= contracts[i].startDate.month && contracts[pos].startDate.month < contracts[i].endDate.month && contracts[pos].startDate.year == contracts[i].startDate.year && contracts[pos].startDate.year == contracts[i].endDate.year) || (contracts[pos].codeVehicle == contracts[i].codeVehicle && contracts[pos].startDate.year >= contracts[i].startDate.year && contracts[pos].startDate.year < contracts[i].endDate.year)) {
            printf("This vehicle was under a contract in the intended date so it was not available\n");
            validateDate(&d);
            contracts[pos].startDate = d;
        }
    }
}

static void deleteContract(contract c[], int pos, size_t *quantity, vehicle vehicles[], customer customers[], size_t quantityVehicles, size_t quantityCustomers) {
    if (c[pos].endDate.day == 0)
        printf("The contract cannot be deleted because it was not closed yet\n");
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

static int searchDate(contract cont[], date date, size_t quantity) {
    int i, enc = -1;
    validateDate(&date);
    for (i = 0; i <= quantity; i++)
        if (cont[i].startDate.day == date.day && cont[i].startDate.month == date.month && cont[i].startDate.year == date.year)// create a function in date
            enc = i;
    return enc;
}

static int searchContract(contract c[], size_t quantityContracts) {// refactor function, date is invalid
    int aux = -1;
    int i, found, insertedCodeValue;
    date date;
    printf("Contract start date\n");
    found = searchDate(c, date, quantityContracts);
    printf("Vehicle code\n");
    insertedCodeValue = readInt(10, 99);
    for (i = 0; i <= quantityContracts; i++) {
        if (c[i].startDate.day == date.day && c[i].startDate.month == date.month && c[i].startDate.year == date.year && c[i].codeVehicle == insertedCodeValue) {
            showContract(c[found]);
            aux = i;
        }
    }
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
            n = readInt(1000, 9999);
            positionCustomer = searchCodeCustomer(customers, quantityCustomers, n);
            if (positionCustomer < 0) {
                printf("Customer not found, try another code\n");
            }
        } while (positionCustomer < 0);
        if (customers[positionCustomer].type == 1) {
            printf("This is a risky client so we cannot proceed with the contract\n");
            return;
        }
        do {
            printf("Vehicle code\n");
            n = readInt(10, 99);
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
        printf("Insert the price per day\n");
        contracts[*quantityContracts].priceDay = readFloat(0.01f, 9999.0f);
        validateDate(&contracts[*quantityContracts].startDate);
        for (i = 0; i < *quantityContracts; i++) {
            while ((contracts[*quantityContracts].codeVehicle == contracts[i].codeVehicle && contracts[*quantityContracts].startDate.day >= contracts[i].startDate.day && contracts[*quantityContracts].startDate.day < contracts[*quantityContracts].endDate.day && contracts[*quantityContracts].startDate.month == contracts[i].startDate.month && contracts[*quantityContracts].startDate.month == contracts[i].endDate.month && contracts[*quantityContracts].startDate.year == contracts[i].startDate.year && contracts[*quantityContracts].startDate.year == contracts[i].endDate.year) || (contracts[*quantityContracts].codeVehicle == contracts[i].codeVehicle && contracts[*quantityContracts].startDate.month >= contracts[i].startDate.month && contracts[*quantityContracts].startDate.month < contracts[i].endDate.month && contracts[*quantityContracts].startDate.year == contracts[i].startDate.year && contracts[*quantityContracts].startDate.year == contracts[i].endDate.year) || (contracts[*quantityContracts].codeVehicle == contracts[i].codeVehicle && contracts[*quantityContracts].startDate.year >= contracts[i].startDate.year && contracts[*quantityContracts].startDate.year < contracts[i].endDate.year)) {
                printf("The vehicle was unavailable for the intended date\n");
                validateDate(&contracts[*quantityContracts].startDate);
            }
        }
        printf("Information: This vehicle is in %s, this will be considered for the start office of the contract\n", officeEnumToText(vehicles[positionVehicle].location));
        contracts[*quantityContracts].startOffice = vehicles[positionVehicle].location;
        vehicles[positionVehicle].location = Unknown;
        (*quantityContracts)++;
    }
}


static void endContract(contract contracts[], int pos, vehicle vehicles[], customer customers[], size_t quantityCustomers, size_t quantityVehicles, size_t quantityContracts) {
    if (contracts[pos].endDate.day != 0)
        printf("\n This contract was already closed\n");
    else {
        char value;
        int i, positionCustomer, positionVehicle;
        printf("\nIs the vehicle in a good status? Yes(y) No(n) ");
        do {
            scanf("%c", &value);
        } while (value != 'y' && value != 'Y' && value != 'n' && value != 'N');
        positionCustomer = searchCodeCustomer(customers, quantityCustomers, contracts[pos].codeCustomer);
        if (value == 'n' || value == 'N') {
            customers[positionCustomer].type = 1;
        }
        customers[positionCustomer].isUnderContract = false;
        positionVehicle = searchCodeVehicle(vehicles, quantityVehicles, contracts[pos].codeVehicle);
        vehicles[positionVehicle].isUnderContract = false;
        printf("Quantity of km\n");
        contracts[pos].quantityKm = readFloat(vehicles[positionVehicle].km, INFINITY);
        vehicles[positionVehicle].km += contracts[pos].quantityKm;
        // insert code to obtain cost
        validateDate(&contracts[pos].endDate);
        for (i = 0; i < quantityContracts; i++) {
            while ((contracts[pos].codeVehicle == contracts[i].codeVehicle && contracts[pos].endDate.day > contracts[i].startDate.day && contracts[pos].endDate.month == contracts[i].startDate.month && contracts[pos].startDate.month == contracts[i].endDate.month && contracts[pos].endDate.year == contracts[i].startDate.year && contracts[pos].endDate.year == contracts[i].endDate.year) || (contracts[pos].codeVehicle == contracts[i].codeVehicle && contracts[pos].endDate.month >= contracts[i].startDate.month && contracts[pos].endDate.month < contracts[i].endDate.month && contracts[pos].endDate.year == contracts[i].startDate.year && contracts[pos].endDate.year == contracts[i].endDate.year) || (contracts[pos].codeVehicle == contracts[i].codeVehicle && contracts[pos].endDate.year >= contracts[i].startDate.year && contracts[pos].endDate.year < contracts[i].endDate.year)) {
                printf("\nThe vehicle was unavailable for the intended date\n");
                validateDate(&contracts[pos].endDate);
            }
        }
        while ((contracts[pos].startDate.day > contracts[pos].endDate.day && contracts[pos].startDate.month == contracts[pos].endDate.month && contracts[pos].startDate.year == contracts[pos].endDate.year) || (contracts[pos].startDate.month > contracts[pos].endDate.month && contracts[pos].startDate.year == contracts[pos].endDate.year) || contracts[pos].startDate.year > contracts[pos].endDate.year) {
            printf("\n Invalid date\n");
            validateDate(&contracts[pos].endDate);
        }
        printf("\nOffice where the vehicle is:\n");
        printf("%s %d %s %d %s %d %s %d %s %d %s %d", officeEnumToText(Braga), Braga, officeEnumToText(Coimbra), Coimbra, officeEnumToText(Guarda), Guarda, officeEnumToText(Faro), Faro, officeEnumToText(Lisbon), Lisbon, officeEnumToText(Porto), Porto);
        contracts[pos].endOffice = readInt(0, 5);
        vehicles[positionVehicle].location = contracts[pos].endOffice;
    }
}

void showContractByVehicleCodeAndStartDateAndShowOptions(contract contracts[], vehicle vehicles[], customer customers[], size_t quantityContracts, size_t quantityVehicles, size_t quantityCustomers) {
    int contractPosition;
    if (quantityContracts == 0) {
        printf("There are no registered contracts\n");
        return;
    }
    contractPosition = searchContract(contracts, quantityContracts);
    if (contractPosition >= 0) {
        showContract(contracts[contractPosition]);
        printf("\nEdit(e) Delete(d) End (t) (Press any other key plus enter to leave this menu)\n");
        unsigned char op;
        do {
            op = getchar();
        } while (op == '\n');
        if (op == 'T' || op == 't') {
            endContract(contracts, contractPosition, vehicles, customers, quantityCustomers, quantityVehicles, quantityContracts);
        } else if (op == 'E' || op == 'e') {
            editContract(contracts, vehicles, contractPosition, quantityVehicles, quantityContracts);
        } else if (op == 'D' || op == 'd') {
            deleteContract(contracts, contractPosition, &quantityContracts, vehicles, customers, quantityVehicles, quantityCustomers);
            printf("Contract deleted successfully\n");
        }
    } else {
        printf("No contract found with data provided\n");
    }
}
