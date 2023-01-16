#include "constants.h"
#include "contract.h"
#include "customer.h"
#include "date.h"
#include "input.h"
#include "vehicle.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char category[][10] = {"capucine", "integral", "perfilada", "furgao", "citadina", "utilitaria", "familiar"};

// L� dados de um customer e guarda no vetor
void inserirCli(customer cli[], int *qtd) {
    int n, i, encontrou = -1;
    char valor[MAX_TXT];

    if (*qtd == MAX_CLI)
        printf("\nDe momento nao admitimos mais clientes!!\n");
    else {
        printf("\n--- Dados do customer ---");
        n = readInt(1000, 9999);
        encontrou = searchCodeClient(cli, *qtd, n);
        printf("\n\t\t encontrou %hd e *qtd %hd ", encontrou, *qtd);
        while (encontrou >= 0)// Significa que � repetido e n�o pode acontecer!!!
        {
            n = readInt(1000, 9999);
            encontrou = searchCodeClient(cli, *qtd, n);
        }
        printf("\n\t\t Fora: ");
        cli[*qtd].code = n;
        readString(valor, 30, "\nNome (max 30 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(cli[*qtd].name, valor);
        readString(valor, 40, "\nMorada (max 40 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(cli[*qtd].address, valor);
        readString(valor, 5, "\nCarta de conducao (max 5 caracteres):");
        printf("\n\t %s \n", valor);
        strcpy(cli[*qtd].driverLicense, valor);
        cli[*qtd].type = 0;
        getchar();
    }
    (*qtd)++;// Incrementa a quantidade de clientes existentes no vector
}

// Esta fun��o difere da fun��o inserirCli pois esta baseia-se em qualquer posi��o da fun��o, modificando-a, logo nao altera o valor da quantidade.
void editarCli(customer cli[], contract cont[], int pos) {
    int i, aux = 0;
    for (i = 0; i < MAX_CONT; i++) {
        if (cont[i].codeCustomer == cli[pos].code && cont[i].endDate.day == 0) {
            printf("\n O customer encontra-se em contract pelo que n�o � poss�vel modific�-lo\n");
            aux++;
        }
    }
    if (aux == 0) {
        int n;
        printf("\n--- Dados do customer ---");
        char valor[MAX_TXT];
        readString(valor, 30, "\nNome (max 30 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(cli[pos].name, valor);
        readString(valor, 40, "\nMorada (max 40 caracteres):");
        printf("\n\t %s ", valor);
        strcpy(cli[pos].address, valor);
        readString(valor, 5, "\nCarta de conducao (max 5 caracteres):");
        printf("\n\t %s \n", valor);
        strcpy(cli[pos].driverLicense, valor);
    }
}

// Esta fun��o difere da fun��o insertVehicle pois esta baseia-se em qualquer posi��o da fun��o, modificando-a, logo nao altera o valor da quantidade.


// Apaga a posi��o desejada pelo utilizador, decrementando a quantidade 1 vez
void apagarCli(customer cli[], contract cont[], int pos, int *qtd) {
    int i, aux = 0;
    for (i = 0; i < MAX_CONT; i++) {
        if (cont[i].codeCustomer == cli[pos].code && cont[i].endDate.day == 0) {
            printf("\n O customer encontra-se em contract pelo que n�o � poss�vel elimin�-lo\n");
            aux++;
        }
    }
    if (aux == 0) {
        int i;
        for (i = pos; i <= *qtd; i++) {
            cli[i] = cli[i + 1];
        }
        (*qtd)--;// como retiramos um elemento do vetor o seu tamanho diminui
    }
}

// Recebe um customer por par�metro e mostra os seus dados
void mostrarCli(customer cli) {
    int i, cat;
    printf("\n--- Dados do customer ---\n");
    printf("\n Codigo: %hd", cli.code);
    printf("\n Nome: %s", cli.name);
    printf("\n Morada: %s", cli.address);
    printf("\n Tipo: %d", cli.type);
    printf("\n Carta de condu��o: %s\n", cli.driverLicense);
}

// Procura um customer e mostra todos os seus dados
int mostrarDadosCli(customer cli[], int qtd) {
    int i, n, encontrou = -1;

    if (qtd == 0)
        printf("\nNao existem clientes registados!!\n");
    else {
        n = readInt(1000, 9999);
        encontrou = searchCodeClient(cli, qtd, n);
        if (encontrou >= 0)
            mostrarCli(cli[encontrou]);
        else
            printf("\nNao existe nenhum customer com codigo = %hd\n", n);
    }
    getchar();
    return encontrou;
}

// Mostrar todos os dados de todos os clientes
void mostrarDadosClis(customer cli[], int qtd) {
    int n, i;
    if (qtd == 0) {
        printf("\nNao existem clientes registados!!\n");
        getchar();
    } else
        for (i = 0; i < qtd; i++) {
            mostrarCli(cli[i]);
            getchar();
        }
}

void limpar_matriz(vehicle vec[], int local[][MAX_ESC]) {

    int l, c;
    for (l = 0; l < MAX_VC; l++) {
        vec[l].code = 0;
        for (c = 0; c < MAX_ESC; c++)
            local[l][c] = 0;
    }
}

void mostrar_matriz(vehicle vec[], int local[][MAX_ESC], int qtd) {

    int l, c;
    printf("               ------------------ ESCRITORIOS -------------------");
    printf("\nVEICULOS       Braga   Coimbra   Guarda   Faro    Lisboa    Porto");
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
    vec[0].km = 12.000;
    vec[0].quantityFuel = 1000.00;
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
        printf("12- Show/Modify/Delete um vehicle\n");
        printf("13- Show data of all vehicles\n");
        printf("14- Show location of all vehicles\n\n");
        printf("----------------- Contract area -----------------\n");
        printf("21- Rent vehicle\n");
        printf("22- Return vehicle || Show/Modify/Delete um contract\n");
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
    int quantityClients = 0, quantityVehicles = 0, quantityContract = 0, quantityDate, clientPosition = -1, vehiclePosition = -1, contractPosition = -1;
    customer clients[MAX_CLI];
    int ch, local[MAX_VC][MAX_ESC];
    vehicle vehicles[MAX_VC];
    contract contracts[MAX_CONT];
    date dates[MAX_CLI];
    char op;
    limpar_matriz(vehicles, local);
    insertData(clients, vehicles, &quantityClients, &quantityVehicles, local);
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
                inserirCli(clients, &quantityClients);
                system("pause");
                break;
            }
            case 2: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                clientPosition = mostrarDadosCli(clients, quantityClients);
                if (clientPosition >= 0) {
                    printf("\n'M'=Modificar 'A'=Apagar\n");
                    op = getchar();
                    if (op == 'M' || op == 'm') {
                        editarCli(clients, contracts, clientPosition);


                        // colocar aqui o c�digo para chamar o m�dulo modificar customer
                    } else if (op == 'A' || op == 'a') {
                        apagarCli(clients, contracts, clientPosition, &quantityClients);
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
                mostrarDadosClis(clients, quantityClients);
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
#endif// seguindo o sugerido na op��o 2
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
                mostrar_matriz(vehicles, local, quantityVehicles);
                system("pause");
                break;
            }
            case 21: {
#ifdef WINDOWS
                system("cls");
#else
                system("clear");
#endif
                startContract(contracts, clients, vehicles, local, dates, quantityClients, quantityVehicles, &quantityContract);
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
                        endContract(contracts, contractPosition, dates, vehicles, clients, quantityClients, quantityVehicles, quantityContract, local);
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
        }
    } while (ch != 0);
    system("PAUSE");
    return 0;
}
