#include "constants.h"
#include "contract.h"
#include "customer.h"
#include "vehicle.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void showMenu() {
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
}

static void readData(char *customersFile, char *vehiclesFile, char *contractsFile, customer customers[], vehicle vehicles[], contract contracts[], size_t *quantityCustomers, size_t *quantityVehicles, size_t *quantityContracts) {
    readCustomers(customersFile, customers, quantityCustomers);
    readVehicles(vehiclesFile, vehicles, quantityVehicles);
    readContracts(contractsFile, contracts, quantityContracts);
}

static void writeData(char *customersFile, char *vehiclesFile, char *contractsFile, customer customers[], vehicle vehicles[], contract contracts[], size_t quantityCustomers, size_t quantityVehicles, size_t quantityContracts) {
    writeCustomers(customersFile, customers, quantityCustomers);
    writeVehicles(vehiclesFile, vehicles, quantityVehicles);
    writeContracts(contractsFile, contracts, quantityContracts);
}

static void end() {
    if (getchar() == '\n') {}
    printf("-----------------------\n");
    printf("Press enter to continue\n");
    while (getchar() != '\n') {}
}

void run() {
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
        showMenu();
        option = readOption(stdin);
        switch (option) {
            case 1: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                insertCustomer(stdin, customers, &quantityCustomers);
                end();
                break;
            }
            case 2: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                manageCustomerByCode(stdin, customers, &quantityCustomers);
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
                insertVehicle(stdin, vehicles, &quantityVehicles);
                end();
                break;
            }
            case 12: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                manageVehicleByCode(stdin, vehicles, &quantityVehicles);
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
                // Default behaviour is empty on purpose. Invalid inputs are handled by readInput.
            }
        }
    } while (option != 0);
    writeData(customersFile, vehiclesFile, contractsFile, customers, vehicles, contracts, quantityCustomers, quantityVehicles, quantityContracts);
}
