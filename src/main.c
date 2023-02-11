#include "constants.h"
#include "contract.h"
#include "customer.h"
#include "vehicle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int showMenuAndGetOption() {
    int op;
    do {
#ifdef WINDOWS
        system("cls");
        system("title Rent-a-car");
#else
        system("clear");
        printf("Rent-a-car\n");
#endif
        printf("----------------------- MENU ----------------------\n\n");
        printf("------------------ Customer Area ------------------\n");
        printf("1 - Add customer\n");
        printf("2 - Show/Modify/Delete a customer\n");
        printf("3 - Show data of all customers\n\n");
        printf("------------------ Vehicle Area -------------------\n");
        printf("11- Add vehicle\n");
        printf("12- Show/Modify/Delete a vehicle\n");
        printf("13- Show data of all vehicles\n");
        printf("14- Show location of all vehicles\n\n");
        printf("------------------ Contract area ------------------\n");
        printf("21- Rent vehicle\n");
        printf("22- Show/Modify/Delete a contract or Return vehicle\n");
        printf("23- Show data of all contracts\n\n");
        printf("0 - Exit\n");
        printf("Insert an option: ");
        int check = scanf("%d", &op);
        if (check != 1) {
            while ((check = fgetc(stdin)) != '\n' && check != EOF) {}
        }
    } while (op != 0 &&
             op != 1 && op != 2 && op != 3 &&
             op != 11 && op != 12 && op != 13 && op != 14 &&
             op != 21 && op != 22 && op != 23);
    return op;
}

void readData(char *customersFile, char *vehiclesFile, char *contractsFile, customer customers[], vehicle vehicles[], contract contracts[], size_t *quantityCustomers, size_t *quantityVehicles, size_t *quantityContracts) {
    readCustomers(customersFile, customers, quantityCustomers);
    readVehicles(vehiclesFile, vehicles, quantityVehicles);
    readContracts(contractsFile, contracts, quantityContracts);
}

void writeData(char *customersFile, char *vehiclesFile, char *contractsFile, customer customers[], vehicle vehicles[], contract contracts[], size_t quantityCustomers, size_t quantityVehicles, size_t quantityContracts) {
    writeCustomers(customersFile, customers, quantityCustomers);
    writeVehicles(vehiclesFile, vehicles, quantityVehicles);
    writeContracts(contractsFile, contracts, quantityContracts);
}

void end() {
    if (getchar() == '\n') {}
    printf("-----------------------\n");
    printf("Press enter to continue\n");
    while (getchar() != '\n') {}
}

int main() {
    size_t quantityCustomers = 0, quantityVehicles = 0, quantityContracts = 0;
    customer customers[MAX_CUSTOMERS];
    int option;
    vehicle vehicles[MAX_VEHICLES];
    contract contracts[MAX_CONTRACTS];
    // variables to read/write data
    char customersFile[14], vehiclesFile[13], contractsFile[14];
#ifdef WINDOWS
    strcat(customersFile, "customers.bin\0");
    strcat(vehiclesFile, "vehicles.bin\0");
    strcat(contractsFile, "contracts.bin\0");
#else
    strcat(customersFile, "customers\0");
    strcat(vehiclesFile, "vehicles\0");
    strcat(contractsFile, "contracts\0");
#endif
    readData(customersFile, vehiclesFile, contractsFile, customers, vehicles, contracts, &quantityCustomers, &quantityVehicles, &quantityContracts);
    do {
#ifdef WINDOWS
        system("cls");
#else
        system("clear");
#endif
        option = showMenuAndGetOption();
        switch (option) {
            case 1: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                insertCustomer(customers, &quantityCustomers);
                end();
                break;
            }
            case 2: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                showCustomerByCodeAndShowOptions(customers, &quantityCustomers);
                end();
                break;
            }
            case 3: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                showAllCustomers(customers, quantityCustomers);
                end();
                break;
            }
            case 11: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                insertVehicle(vehicles, &quantityVehicles);
                end();
                break;
            }
            case 12: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                showVehicleByCodeAndShowOptions(vehicles, &quantityVehicles);
                end();
                break;
            }
            case 13: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                showAllVehicles(vehicles, quantityVehicles);
                end();
                break;
            }

            case 14: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                showVehiclesLocation(vehicles, quantityVehicles);
                end();
                break;
            }
            case 21: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                startContract(contracts, customers, vehicles, quantityCustomers, quantityVehicles, &quantityContracts);
                end();
                break;
            }
            case 22: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                showContractByVehicleCodeAndStartDateAndShowOptions(contracts, vehicles, customers, &quantityContracts, quantityVehicles, quantityCustomers);
                end();
                break;
            }
            case 23: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                showContracts(contracts, quantityContracts);
                end();
                break;
            }
            default: {
            }
        }
    } while (option != 0);
    writeData(customersFile, vehiclesFile, contractsFile, customers, vehicles, contracts, quantityCustomers, quantityVehicles, quantityContracts);
    return 0;
}
