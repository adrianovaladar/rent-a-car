#include "constants.h"
#include "contract.h"
#include "customer.h"
#include "vehicle.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void showMenu() {
#ifdef _WIN32
        system("cls");
        system("title Rent-a-car");
#else
        system("clear");
        printf("Rent-a-car\n");
#endif
        printf("----------------------- MENU ----------------------\n\n");
        printf("------------------ Customer Area ------------------\n");
        printf("1 - Add customer\n");
        printf("2 - Manage a customer\n");
        printf("3 - Show data of all customers\n\n");
        printf("------------------ Vehicle Area -------------------\n");
        printf("11- Add vehicle\n");
        printf("12- Manage a vehicle\n");
        printf("13- Show data of all vehicles\n");
        printf("14- Show location of all vehicles\n\n");
        printf("------------------ Contract area ------------------\n");
        printf("21- Rent vehicle\n");
        printf("22- Manage a contract\n");
        printf("23- Show data of all contracts\n\n");
        printf("0 - Exit\n");
}

static void readData(const char *customersFile, const char *vehiclesFile, char *contractsFile, customer *customers, vehicle *vehicles, contract *contracts, size_t *quantityCustomers, size_t *quantityVehicles, size_t *quantityContracts) {
    readCustomers(customersFile, customers, quantityCustomers);
    readVehicles(vehiclesFile, vehicles, quantityVehicles);
    readContracts(contractsFile, contracts, quantityContracts);
}

static void writeData(const char *customersFile, const char *vehiclesFile, char *contractsFile, const customer *customers, const vehicle *vehicles, const contract *contracts, const size_t quantityCustomers, const size_t quantityVehicles, const size_t quantityContracts) {
    writeCustomers(customersFile, customers, quantityCustomers);
    writeVehicles(vehiclesFile, vehicles, quantityVehicles);
    writeContracts(contractsFile, contracts, quantityContracts);
}

static void end() {
    if (getchar() == '\n') {
        // ignore if a new line is detected
    }
    printf("-----------------------\n");
    printf("Press enter to continue\n");
    while (getchar() != '\n') {
        // wait for a new line
    }
}

void run() {
    size_t quantityCustomers = 0;
    size_t quantityVehicles = 0;
    size_t quantityContracts = 0;
    customer customers[MAX_CUSTOMERS];
    int option;
    vehicle vehicles[MAX_VEHICLES];
    contract contracts[MAX_CONTRACTS];
    // variables to read/write data
    char customersFile[14];
    char vehiclesFile[13];
    char contractsFile[14];
#ifdef _WIN32
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
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        showMenu();
        option = readOption(stdin, stdout);
        switch (option) {
            case 1: {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                insertCustomer(stdin, customers, &quantityCustomers);
                end();
                break;
            }
            case 2: {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                manageCustomerByCode(stdin, customers, &quantityCustomers);
                end();
                break;
            }
            case 3: {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                showAllCustomers(customers, quantityCustomers);
                end();
                break;
            }
            case 11: {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                insertVehicle(stdin, vehicles, &quantityVehicles);
                end();
                break;
            }
            case 12: {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                manageVehicleByCode(stdin, vehicles, &quantityVehicles);
                end();
                break;
            }
            case 13: {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                showAllVehicles(vehicles, quantityVehicles);
                end();
                break;
            }

            case 14: {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                showVehiclesLocation(vehicles, quantityVehicles);
                end();
                break;
            }
            case 21: {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                startContract(stdin, contracts, customers, vehicles, &quantityContracts, quantityCustomers, quantityVehicles);
                end();
                break;
            }
            case 22: {
#ifdef _WIN32
                system("cls");
#else
                system("clear");
#endif
                manageContractByVehicleCodeAndStartDate(stdin, contracts, vehicles, customers, &quantityContracts, quantityVehicles, quantityCustomers);
                end();
                break;
            }
            case 23: {
#ifdef _WIN32
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
