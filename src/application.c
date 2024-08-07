#include "constants.h"
#include "contract.h"
#include "customer.h"
#include "vehicle.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
    #define CLEAR_CONSOLE() system("cls")
#else
    #define CLEAR_CONSOLE() system("clear")
#endif

static void showMenu() {
    CLEAR_CONSOLE();
#ifdef _WIN32
        system("title Rent-a-car");
#else
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

static void readData(logger *logger, const char *customersFile, const char *vehiclesFile, char *contractsFile, customer *customers, vehicle *vehicles, contract *contracts, size_t *quantityCustomers, size_t *quantityVehicles, size_t *quantityContracts) {
    readCustomers(stdout, logger, customersFile, customers, quantityCustomers);
    readVehicles(stdout, logger, vehiclesFile, vehicles, quantityVehicles);
    readContracts(stdout, logger, contractsFile, contracts, quantityContracts);
}

static void writeData(logger *logger, const char *customersFile, const char *vehiclesFile, char *contractsFile, const customer *customers, const vehicle *vehicles, const contract *contracts, const size_t quantityCustomers, const size_t quantityVehicles, const size_t quantityContracts) {
    writeCustomers(stdout, logger, customersFile, customers, quantityCustomers);
    writeVehicles(stdout, logger, vehiclesFile, vehicles, quantityVehicles);
    writeContracts(stdout, logger, contractsFile, contracts, quantityContracts);
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
    logger *logger = getLoggerInstance();
#ifdef _WIN32
    strcat(customersFile, "customers.bin\0");
    strcat(vehiclesFile, "vehicles.bin\0");
    strcat(contractsFile, "contracts.bin\0");
#else
    strcat(customersFile, "customers\0");
    strcat(vehiclesFile, "vehicles\0");
    strcat(contractsFile, "contracts\0");
#endif
    readData(logger, customersFile, vehiclesFile, contractsFile, customers, vehicles, contracts, &quantityCustomers, &quantityVehicles, &quantityContracts);
    do {
        CLEAR_CONSOLE();
        showMenu();
        option = readOption(stdin, stdout);
        switch (option) {
            case 1: {
                CLEAR_CONSOLE();
                insertCustomer(stdin, stdout, logger, customers, &quantityCustomers);
                end();
                break;
            }
            case 2: {
                CLEAR_CONSOLE();
                manageCustomerByCode(stdin, stdout, logger, customers, &quantityCustomers);
                end();
                break;
            }
            case 3: {
                CLEAR_CONSOLE();
                showAllCustomers(stdout, customers, quantityCustomers);
                end();
                break;
            }
            case 11: {
                CLEAR_CONSOLE();
                insertVehicle(stdin, stdout, logger, vehicles, &quantityVehicles);
                end();
                break;
            }
            case 12: {
                CLEAR_CONSOLE();
                manageVehicleByCode(stdin, stdout, logger, vehicles, &quantityVehicles);
                end();
                break;
            }
            case 13: {
                CLEAR_CONSOLE();
                showAllVehicles(stdout, vehicles, quantityVehicles);
                end();
                break;
            }

            case 14: {
                CLEAR_CONSOLE();
                showVehiclesLocation(stdout, vehicles, quantityVehicles);
                end();
                break;
            }
            case 21: {
                CLEAR_CONSOLE();
                startContract(stdin, stdout, logger, contracts, customers, vehicles, &quantityContracts, quantityCustomers, quantityVehicles);
                end();
                break;
            }
            case 22: {
                CLEAR_CONSOLE();
                manageContractByVehicleCodeAndStartDate(stdin, stdout, logger, contracts, vehicles, customers, &quantityContracts, quantityVehicles, quantityCustomers);
                end();
                break;
            }
            case 23: {
                CLEAR_CONSOLE();
                showContracts(stdout, contracts, quantityContracts);
                end();
                break;
            }
            default: {
                // Default behaviour is empty on purpose. Invalid inputs are handled by readInput.
            }
        }
    } while (option != 0);
    writeData(logger, customersFile, vehiclesFile, contractsFile, customers, vehicles, contracts, quantityCustomers, quantityVehicles, quantityContracts);
}
