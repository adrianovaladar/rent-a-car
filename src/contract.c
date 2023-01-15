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
        printf("\nO contract n�o pode ser eliminado pois ainda n�o foi finalizado\n");
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
    int i, found, codvec = -1;
    printf("Insert the start date of the contract\n");
    found = searchDate(c, data, qtd);
    printf("Insert the code of the vehicle\n");
    readInt(10, 99);
    for (i = 0; i <= qtd; i++) {
        if (c[i].startDate.day == data[0].day && c[i].startDate.month == data[0].month && c[i].startDate.year == data[0].year && c[i].codeVehicle == codvec) {
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
