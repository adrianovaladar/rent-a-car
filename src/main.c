#include "constants.h"
#include "contract.h"
#include "customer.h"
#include "date.h"
#include "vehicle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char category[][10] = {"capucine", "integral", "perfilada", "furgao", "citadina", "utilitaria", "familiar"};

void cleanMatrix(vehicle vec[], int local[][MAX_ESC]) {

    int l, c;
    for (l = 0; l < MAX_VC; l++) {
        vec[l].code = 0;
        for (c = 0; c < MAX_ESC; c++)
            local[l][c] = 0;
    }
}

void showMatrix(vehicle vec[], int local[][MAX_ESC]) {

    int l, c;
    printf("               ------------------ ESCRITORIOS -------------------");
    printf("\nVEHICLES       Braga   Coimbra   Guarda   Faro    Lisboa    Porto");
    for (l = 0; l < 6; l++)//for(l=0;l<qtd;l++)
    {
        printf("\n%-9u", vec[l].code);
        for (c = 0; c < MAX_ESC; c++)
            printf("%9u", local[l][c]);
    }
    getchar();
}

void insertData(customer cli[], vehicle vec[], int *qtdcli, int *qtdvec, int local[][MAX_ESC]) {
    int n;
    cli[0].code = 1000;
    strcpy(cli[0].name, "customer 1");
    strcpy(cli[0].address, "Example Address 1");
    strcpy(cli[0].driverLicense, "P-12345678");
    cli[0].type = 0;
    (*qtdcli)++;

    cli[1].code = 1001;
    strcpy(cli[1].name, "customer 2");
    strcpy(cli[1].address, "Example Address 2");
    strcpy(cli[1].driverLicense, "P-98765432");
    cli[1].type = 1;
    (*qtdcli)++;

    vec[0].code = 10;
    strcpy(vec[0].brand, "Fiat");
    strcpy(vec[0].model, "Ducato");
    strcpy(vec[0].registrationPlate, "LA-35-61");
    vec[0].isUnderContract = false;
    vec[0].km = 12.000f;
    vec[0].quantityFuel = 1000.00f;
    vec[0].codeCategory = 0;
    n = 2;
    (local[0][n])++;
    vec[0].startPlace = n;

    (*qtdvec)++;
}

int showMenu() {
    int op;
    do {
#ifdef WINDOWS
        system("cls");
        system("title Rent-a-car");
#else
        system("clear");
        printf("Rent-a-car\n");
#endif
        printf("--------------------- MENU ----------------------\n\n");
        printf("----------------- Customer Area -----------------\n");
        printf("1 - Add customer\n");
        printf("2 - Show/Modify/Delete a customer\n");
        printf("3 - Show data of all customers\n\n");
        printf("----------------- Vehicle Area ------------------\n");
        printf("11- Add vehicle\n");
        printf("12- Show/Modify/Delete a vehicle\n");
        printf("13- Show data of all vehicles\n");
        printf("14- Show location of all vehicles\n\n");
        printf("----------------- Contract area -----------------\n");
        printf("21- Rent vehicle\n");
        printf("22- Return vehicle || Show/Modify/Delete a contract\n");
        printf("23- Show data of all contracts\n\n");
        printf("0 - Exit\n");
        printf("Insert an option:");
        scanf("%d", &op);
    } while (op != 0 &&
             op != 1 && op != 2 && op != 3 &&
             op != 11 && op != 12 && op != 13 && op != 14 &&
             op != 21 && op != 22 && op != 23);
    return op;
}

int main() {
    int quantityCustomers = 0, quantityVehicles = 0, quantityContract = 0, clientPosition, vehiclePosition, contractPosition;
    customer customer[MAX_CLI];
    int ch, local[MAX_VC][MAX_ESC];
    vehicle vehicles[MAX_VC];
    contract contracts[MAX_CONT];
    date dates[MAX_CLI];
    char op;
    cleanMatrix(vehicles, local);
    insertData(customer, vehicles, &quantityCustomers, &quantityVehicles, local);
    do {
#ifdef WINDOWS
        system("cls");
#else
        system("clear");
#endif
        ch = showMenu();
        switch (ch) {
            case 1: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                insertCustomer(customer, &quantityCustomers);
                printf("Press enter to continue\n");
                while (getchar() != '\n')
                    ;
                break;
            }
            case 2: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                clientPosition = mostrarDadosCli(customer, quantityCustomers);
                if (clientPosition >= 0) {
                    printf("\n'M'=Modificar 'A'=Apagar\n");
                    op = getchar();
                    if (op == 'M' || op == 'm') {
                        editCustomer(customer, clientPosition);


                        // colocar aqui o c�digo para chamar o m�dulo modificar customer
                    } else if (op == 'A' || op == 'a') {
                        deleteCustomer(customer, clientPosition, &quantityCustomers);
                        // colocar aqui o c�digo para chamar o m�dulo apagar customer
                    }
                }
                system("pause");
                break;
            }
            case 3: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                mostrarDadosClis(customer, quantityCustomers);
                system("pause");
                break;
            }

            case 11: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                insertVehicle(vehicles, &quantityVehicles, local);
                // colocar aqui o c�digo para chamar o m�dulo inserir vehicle
                system("pause");
                break;
            }
            case 12: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                vehiclePosition = showVehicleByCode(vehicles, quantityVehicles);
                if (vehiclePosition >= 0) {
                    printf("\n'M'=Modificar 'A'=Apagar\n");
                    op = getchar();
                    if (op == 'M' || op == 'm') {
                        editVehicle(vehicles, vehiclePosition, local);

                    }
                    // colocar aqui o c�digo para chamar o m�dulo modificar vehicle
                    else if (op == 'A' || op == 'a') {
                        deleteVehicle(vehicles, vehiclePosition, &quantityVehicles, local);
                    }
                }// colocar aqui o c�digo para chamar o m�dulo apagar vehicle
                system("pause");
                break;
            }
            case 13: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                showAllVehicles(vehicles, quantityVehicles);
                // Colocar aqui c�digo para chamar m�dulo mostrar veiculos
                printf("Press any key to continue\n");
                getchar();
                break;
            }

            case 14: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                showMatrix(vehicles, local);
                system("pause");
                break;
            }
            case 21: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                startContract(contracts, customer, vehicles, local, dates, quantityCustomers, quantityVehicles, &quantityContract);
                // Colocar aqui o c�digo para chamar o m�dulo alugar vehicle
                system("pause");
                break;
            }
            case 22: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                // Colocar aqui o c�digo para chamar o m�dulo modificar contract e/ou apagar contract
                contractPosition = ShowContract(contracts, dates, quantityContract);
                if (contractPosition >= 0) {
                    printf("\n 'T'=Terminar contract 'M'=Modificar 'A'=Apagar\n");
                    op = getchar();
                    if (op == 'T' || op == 't') {
                        endContract(contracts, contractPosition, dates, vehicles, customer, quantityCustomers, quantityVehicles, quantityContract, local);
                        //Colocar aqui o c�digo para devolver ve�culo
                    }
                    if (op == 'M' || op == 'm') {
                        editContract(contracts, vehicles, contractPosition, dates, quantityContract, quantityContract);

                        // colocar aqui o c�digo para chamar o m�dulo modificar contract
                    } else if (op == 'A' || op == 'a') {
                        deleteContract(contracts, contractPosition, &quantityContract);
                    }
                }
                system("pause");
                break;
            }
            case 23: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                showContractData(contracts, quantityContract);
                // Colocar aqui o c�digo para chamar o m�dulo mostrar contratos
                system("pause");
                break;
            }
            default: {
            }
        }
    } while (ch != 0);
    system("PAUSE");
    return 0;
}
