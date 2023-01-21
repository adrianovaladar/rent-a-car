#include "contract.h"
#include "input.h"
#include "vehicle.h"
#include <stdio.h>

void showContractData(contract c[], int qtd) {
    int i, j;
    char valor;
    contract contaux[0];
    if (qtd == 0) {
        printf("\nThere are no registered contracts\n");
        getchar();
    } else {
        for (i = 0; i < qtd; i++) {
            showContract(c[i]);
        }
        if (qtd > 1) {
            printf("\nSort by date? Yes(y) No(n)\n");
            scanf("%c", &valor);
            while (valor != 'n' && valor != 'N' && valor != 'y' && valor != 'Y') {
                scanf("%c", &valor);
            }
            if (valor == 'y' || valor == 'Y') {
                for (j = 1; j < qtd; j++) {
                    for (i = 0; i < qtd - 1; i++) {
                        if ((c[i].startDate.day > c[i + 1].startDate.day && c[i].startDate.month == c[i + 1].startDate.month && c[i].startDate.year == c[i + 1].startDate.year) || (c[i].startDate.month > c[i + 1].startDate.month && c[i].startDate.year == c[i + 1].startDate.year) || (c[i].startDate.year > c[i + 1].startDate.year)) {
                            contaux[0] = c[i];
                            c[i] = c[i + 1];
                            c[i + 1] = contaux[0];
                        }
                    }
                }
                for (i = 0; i < qtd; i++) {
                    showContract(c[i]);
                }
            }
        }
    }
    getchar();
}

void showContract(contract c) {
    printf("\n--- Contract data ---\n");
    printf("\n Customer Code: %d", c.codeCustomer);
    printf("\n Vehicle code: %d", c.codeVehicle);
    printf("\n Price by day: %.2f", c.priceDay);
    printf("\n Price by km: %.2f", c.priceKm);
    printf("\n Quantity kms: %.2f", c.quantityKm);
    printf("\n Start date: day %d month %d year %d", c.startDate.day, c.startDate.month, c.startDate.year);
    printf("\n End date: day %d month %d year %d ", c.endDate.day, c.endDate.month, c.endDate.year);
    printf("\n Start office: %d", c.startOffice);
    if (!isEmptyDate(c.endDate)) {
        printf("\n End office: %d", c.endOffice);
        printf("\n Note: \n 0 Braga 1 Coimbra 2 Guarda 3 Faro 4 Lisboa 5 Porto");
    }
}

void editContract(contract cont[], vehicle vec[], int pos, date d[], int qtdvec, int qtd) {
    if (cont[pos].endDate.year != 0)
        printf("\nNot possible to edit this contract because it is already closed\n");
    else {

        int i, encontrou;
        encontrou = searchCodeVehicle(vec, qtdvec, cont[pos].codeVehicle);
        if (vec[encontrou].codeCategory > 3) {
            printf("\nInsert the price per day\n");
            cont[pos].priceDay = readFloat(0.01f, 9999);
        } else {
            printf("\nInsert the price per km\n");
            cont[pos].priceKm = readFloat(0.01f, 9999);
        }
        validateDate(d);
        cont[pos].startDate = d[0];
        for (i = 0; i < qtd; i++)
            while ((cont[pos].codeVehicle == cont[i].codeVehicle && cont[pos].startDate.day >= cont[i].startDate.day && cont[pos].startDate.day < cont[pos].endDate.day && cont[pos].startDate.month == cont[i].startDate.month && cont[pos].startDate.month == cont[i].endDate.month && cont[pos].startDate.year == cont[i].startDate.year && cont[pos].startDate.year == cont[i].endDate.year) || (cont[pos].codeVehicle == cont[i].codeVehicle && cont[pos].startDate.month >= cont[i].startDate.month && cont[pos].startDate.month < cont[i].endDate.month && cont[pos].startDate.year == cont[i].startDate.year && cont[pos].startDate.year == cont[i].endDate.year) || (cont[pos].codeVehicle == cont[i].codeVehicle && cont[pos].startDate.year >= cont[i].startDate.year && cont[pos].startDate.year < cont[i].endDate.year)) {
                printf("\nThis vehicle was under a contract in the intended date so it was not available\n");
                validateDate(d);
                cont[pos].startDate = d[0];
            }
    }
}

void deleteContract(contract c[], int pos, int *qtd) {
    if (c[pos].endDate.day == 0)
        printf("\nThe contract cannot be deleted because it was not closed yet\n");
    else {
        int i;
        for (i = pos; i <= *qtd; i++) {
            c[i] = c[i + 1];
        }
        (*qtd)--;
    }
}

int ShowContract(contract c[], date data[], int qtd) {
    int aux = -1;
    if (qtd == 0) {
        printf("\nThere are no registered contracts\n");
        return aux;
    }
    int i, found, insertedCodeValue;
    printf("Insert the start date of the contract\n");
    found = searchDate(c, data, qtd);
    printf("Insert the code of the vehicle\n");
    insertedCodeValue = readInt(10, 99);
    for (i = 0; i <= qtd; i++) {
        if (c[i].startDate.day == data[0].day && c[i].startDate.month == data[0].month && c[i].startDate.year == data[0].year && c[i].codeVehicle == insertedCodeValue) {
            showContract(c[found]);
            aux = i;
        }
    }
    getchar();
    return aux;
}

int searchDate(contract cont[], date data[], int qtd) {
    int i, enc = -1;
    validateDate(data);
    for (i = 0; i <= qtd; i++)
        if (cont[i].startDate.day == data[0].day && cont[i].startDate.month == data[0].month && cont[i].startDate.year == data[0].year)// create a function in date
            enc = i;
    return enc;
}


void startContract(contract contracts[], customer customers[], vehicle vehicles[], int local[][MAX_OFFICES], date data[], int qtdcli, int qtdvec, int *qtd) {
    if (*qtd == MAX_CONTRACTS)
        printf("We reached our full capacity of contracts. Please come back later");
    else {
        int n, positionCustomer, positionVehicle, aux = 0, i;
        if (qtdvec == 0 || qtdcli == 0)
            printf("There are no registered clients or vehicles so a contract cannot be startedt\n");
        else {
            printf("\nInsert code number of customers\n");
            do {
                n = readInt(1000, 9999);
                positionCustomer = searchCodeClient(customers, qtdcli, n);
                printf("\n\t\t position %d and *qtd %d ", positionCustomer, *qtd);
            } while (positionCustomer < 0);
            if (customers[positionCustomer].type == 1) {
                printf("\nThis is a risky client so we cannot proceed with the contract\n");
                return;
            }
            printf("\nInsert code number of the vehicle\n");
            do {
                n = readInt(10, 99);
                positionVehicle = searchCodeVehicle(vehicles, qtdvec, n);
                printf("\n\t\t position %d and *qtd %d ", positionVehicle, *qtd);
            } while (positionVehicle < 0);
            if (vehicles[positionVehicle].isUnderContract == true) {
                printf("\nThe vehicle is unavailable, not possible to proceed\n");
                return;
            }
            customers[positionCustomer].isUnderContract = true;
            contracts[*qtd].codeCustomer = n;
            vehicles[positionVehicle].isUnderContract = true;
            contracts[*qtd].codeVehicle = n;
            if (vehicles[positionVehicle].codeCategory > 3) {
                printf("\nInsert the price per day\n");
                contracts[*qtd].priceDay = readFloat(0.01f, 9999.0f);
            } else {
                printf("\nInsert the price per km\n");
                contracts[*qtd].priceKm = readFloat(0.01f, 9999.0f);
            }
            validateDate(data);
            contracts[*qtd].startDate = data[0];
            for (i = 0; i < *qtd; i++) {
                while ((contracts[*qtd].codeVehicle == contracts[i].codeVehicle && contracts[*qtd].startDate.day >= contracts[i].startDate.day && contracts[*qtd].startDate.day < contracts[*qtd].endDate.day && contracts[*qtd].startDate.month == contracts[i].startDate.month && contracts[*qtd].startDate.month == contracts[i].endDate.month && contracts[*qtd].startDate.year == contracts[i].startDate.year && contracts[*qtd].startDate.year == contracts[i].endDate.year) || (contracts[*qtd].codeVehicle == contracts[i].codeVehicle && contracts[*qtd].startDate.month >= contracts[i].startDate.month && contracts[*qtd].startDate.month < contracts[i].endDate.month && contracts[*qtd].startDate.year == contracts[i].startDate.year && contracts[*qtd].startDate.year == contracts[i].endDate.year) || (contracts[*qtd].codeVehicle == contracts[i].codeVehicle && contracts[*qtd].startDate.year >= contracts[i].startDate.year && contracts[*qtd].startDate.year < contracts[i].endDate.year)) {
                    printf("\nThe vehicle was unavailable for the intended date\n");
                    validateDate(data);
                    contracts[*qtd].startDate = data[0];
                }
            }
            for (i = 0; i < *qtd; i++)
                if (contracts[*qtd].codeVehicle == contracts[i].codeVehicle)
                    aux++;

            if (aux == 0)
                contracts[*qtd].startOffice = vehicles[positionVehicle].startPlace;
            else if (aux > 0) {
                for (i = 0; i < *qtd; i++)
                    if (contracts[*qtd].codeVehicle == contracts[i].codeVehicle)
                        aux = i;
                contracts[*qtd].startOffice = contracts[aux].endOffice;
            }
            (*qtd)++;
            for (i = 0; i < MAX_OFFICES; i++) {
                if (local[positionVehicle][i] == 1)
                    (local[positionVehicle][i])--;
            }
        }
    }
}


void endContract(contract contracts[], int pos, date data[], vehicle vehicles[], customer customers[], int quantityCustomers, int quantityVehicles, int quantityContracts, int local[][MAX_OFFICES]) {
    if (contracts[pos].endDate.day != 0)
        printf("\n This contract was already closed\n");
    else {
        char valor2 = '?';
        int i, positionCustomer, positionVehicle;
        float cost;
        printf("\nIs the vehicle in a good status? Yes(y) No(n)\n");
        valor2 = '?';
        while (valor2 != 'y' && valor2 != 'Y' && valor2 != 'n' && valor2 != 'N') {
            scanf("%c", &valor2);
        }
        positionCustomer = searchCodeClient(customers, quantityCustomers, contracts[pos].codeCustomer);
        if (valor2 == 'n' || valor2 == 'N') {
            customers[positionCustomer].type = 1;
        }
        customers[positionCustomer].isUnderContract = false;
        positionVehicle = searchCodeVehicle(vehicles, quantityVehicles, contracts[pos].codeVehicle);
        vehicles[positionVehicle].isUnderContract = false;

        if (vehicles[positionVehicle].codeCategory < 4) {
            printf("\n Insert the quantity of kms\n");
            contracts[pos].quantityKm = readFloat(0.01f, 5000.0f);
            vehicles[positionVehicle].km = contracts[pos].quantityKm + vehicles[positionVehicle].km;
            cost = contracts[pos].quantityKm * contracts[pos].priceKm;
            printf("\nCost: %.2f\n", cost);
        }
        validateDate(data);
        contracts[pos].endDate = data[0];
        for (i = 0; i < quantityContracts; i++) {
            while ((contracts[pos].codeVehicle == contracts[i].codeVehicle && contracts[pos].endDate.day > contracts[i].startDate.day && contracts[pos].endDate.month == contracts[i].startDate.month && contracts[pos].startDate.month == contracts[i].endDate.month && contracts[pos].endDate.year == contracts[i].startDate.year && contracts[pos].endDate.year == contracts[i].endDate.year) || (contracts[pos].codeVehicle == contracts[i].codeVehicle && contracts[pos].endDate.month >= contracts[i].startDate.month && contracts[pos].endDate.month < contracts[i].endDate.month && contracts[pos].endDate.year == contracts[i].startDate.year && contracts[pos].endDate.year == contracts[i].endDate.year) || (contracts[pos].codeVehicle == contracts[i].codeVehicle && contracts[pos].endDate.year >= contracts[i].startDate.year && contracts[pos].endDate.year < contracts[i].endDate.year)) {
                printf("\nThe vehicle was unavailable for the intended date\n");
                validateDate(data);
                contracts[pos].startDate = data[0];
            }
        }
        while ((contracts[pos].startDate.day > contracts[pos].endDate.day && contracts[pos].startDate.month == contracts[pos].endDate.month && contracts[pos].startDate.year == contracts[pos].endDate.year) || (contracts[pos].startDate.month > contracts[pos].endDate.month && contracts[pos].startDate.year == contracts[pos].endDate.year) || contracts[pos].startDate.year > contracts[pos].endDate.year) {
            printf("\n Invalid date\n");
            validateDate(data);
            contracts[pos].endDate = data[0];
        }
        printf("\nOffice where the vehicle is:");
        printf("\n0 Braga 1 Coimbra 2 Guarda 3 Faro 4 Lisboa 5 Porto");
        int aux = readInt(0, 5);
        contracts[pos].endOffice = aux;
        (local[positionVehicle][aux])++;
    }
}
