#include "vehicle.h"
#include "constants.h"
#include "contract.h"
#include "input.h"
#include <stdio.h>
#include <string.h>

void insertVehicle(vehicle vec[], int *qtd, int local[][MAX_ESC]) {
    int n, i, encontrou = -1;
    char valor[MAX_TXT], valor2;

    if (*qtd == MAX_VC)
        printf("\nDe momento nao admitimos mais carros!!\n");
    else {
        printf("\n--- Dados do carro ---");
        n = readInt(10, 99);
        encontrou = searchCodeVehicle(vec, *qtd, n);
        printf("\n\t\t encontrou %hd e *qtd %hd ", encontrou, *qtd);
        while (encontrou >= 0)// Significa que � repetido e n�o pode acontecer!!!
        {
            n = readInt(10, 99);
            encontrou = searchCodeVehicle(vec, *qtd, n);
        }
        printf("\n\t\t Fora: ");
        vec[*qtd].code = n;
        readChars(valor, 10, "\nMarca (max 10 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(vec[*qtd].brand, valor);
        readChars(valor, 10, "\nModelo (max 10 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(vec[*qtd].model, valor);
        readChars(valor, 8, "\nMatricula (max 8 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(vec[*qtd].registrationPlate, valor);
        printf("\nC�digo Categoria:\n");
        vec[*qtd].codeCategory = readInt(0, 6);
        vec[*qtd].state = 'd';
        //Atrav�s da category � definido se se trata de uma caravana ou autocaravana, o que ir� ditar diferen�as em todas as fun��es do contract.
        if (vec[*qtd].codeCategory < 4) {
            printf("\nKms:\n");
            vec[*qtd].km = readFloat(0, 9999);
            printf("\nQuantidade de Combust�vel\n");
            vec[*qtd].quantityFuel = readFloat(0, 9999);
        }
        printf("\nEscritorio onde se encontra o vehicle");
        printf("\n0 Braga 1 Coimbra 2 Guarda 3 Faro 4 Lisboa 5 Porto");
        n = readInt(0, 5);
        (local[*qtd][n])++;
        vec[*qtd].startPlace = n;
        (*qtd)++;// Incrementa a quantidade de ve�culos existentes no vector
    }
}

int searchCodeVehicle(vehicle vec[], int qtd, int cod) {
    int i, enc = -1;

    for (i = 0; i <= qtd && enc == -1; i++)
        if (vec[i].code == cod)
            enc = i;

    return enc;
}

void editVehicle(vehicle vec[], contract cont[], int pos, int local[][MAX_ESC]) {
    int i, aux = 0;
    for (i = 0; i < MAX_CONT; i++) {
        if (cont[i].codeVehicle == vec[pos].code && cont[i].endDate.day == 0) {
            printf("\n O ve�culo encontra-se em contract pelo que n�o � poss�vel modific�-lo\n");
            aux++;
        }
    }
    if (aux == 0) {
        int n, encontrou = -1, i;
        char valor[MAX_TXT], valor2 = 'f';
        printf("\n--- Dados do carro ---");
        readChars(valor, 10, "\nMarca (max 10 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(vec[pos].brand, valor);
        readChars(valor, 10, "\nModelo (max 10 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(vec[pos].model, valor);
        readChars(valor, 8, "\nMatricula (max 8 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(vec[pos].registrationPlate, valor);
        printf("\nC�digo Categoria:\n");
        vec[pos].codeCategory = readInt(0, 6);
        //Atrav�s da category � definido se se trata de uma caravana ou autocaravana, o que ir� ditar diferen�as em todas as fun��es do contract.
        if (vec[pos].codeCategory < 4) {
            printf("\nKms:\n");
            vec[pos].km = readFloat(0, 9999);
            printf("\nQuantidade de Combust�vel\n");
            vec[pos].quantityFuel = readFloat(0, 9999);
        } else if (vec[pos].codeCategory >= 4) {
            vec[pos].km = 0;
            vec[pos].quantityFuel = 0;
        }
        for (i = 0; i <= MAX_ESC; i++) {
            if (local[pos][i] == 1)
                (local[pos][i])--;
        }
        printf("\nEscritorio onde se encontra o vehicle");
        printf("\n0 Braga 1 Coimbra 2 Guarda 3 Faro 4 Lisboa 5 Porto");
        n = readInt(0, 5);
        (local[pos][n])++;
        vec[pos].startPlace = n;
    }
}

void deleteVehicle(vehicle vec[], contract cont[], int pos, int *qtd, int local[][MAX_ESC]) {
    int i, aux = 0;
    for (i = 0; i < MAX_CONT; i++) {
        if (cont[i].codeVehicle == vec[pos].code && cont[i].endDate.day == 0) {
            printf("\n O ve�culo encontra-se em contract pelo que n�o � poss�vel elimin�-lo\n");
            aux++;
        }
    }
    if (aux == 0) {
        for (i = pos; i <= *qtd; i++) {
            vec[i] = vec[i + 1];
        }
        (*qtd)--;// como retiramos um elemento do vetor o seu tamanho diminui

        for (i = 0; i <= MAX_ESC; i++) {
            if (local[pos][i] == 1)
                (local[pos][i])--;
        }
    }
}