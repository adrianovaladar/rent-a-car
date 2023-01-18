#include "customer.h"
#include "constants.h"
#include "input.h"
#include <stdio.h>
#include <string.h>

int searchCodeClient(customer cli[], int qtd, int cod) {
    int i, enc = -1;

    for (i = 0; i <= qtd && enc == -1; i++)
        if (cli[i].code == cod)
            enc = i;

    return enc;
}

// L� dados de um customer e guarda no vetor
void insertCustomer(customer cli[], int *qtd) {
    int n, i, encontrou = -1;
    char valor[MAX_TXT];

    if (*qtd == MAX_CLI)
        printf("\nDe momento nao admitimos mais clientes!!\n");
    else {
        printf("\n--- Dados do customer ---");
        n = readInt(1000, 9999);
        encontrou = searchCodeClient(cli, *qtd, n);
        printf("\n\t\t encontrou %hd e *qtd %hd ", encontrou, *qtd);
        while (encontrou >= 0) {
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

// Esta fun��o difere da fun��o insertCustomer pois esta baseia-se em qualquer posi��o da fun��o, modificando-a, logo nao altera o valor da quantidade.
void editCustomer(customer cli[], int pos) {
    int i, aux = 0;
    if (cli[pos].isUnderContract) {
        printf("\nThe vehicle is under a contract at the moment, please come back later\n");
        return;
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

void deleteCustomer(customer cli[], int pos, int *qtd) {
    int aux = 0;
    if (cli[pos].isUnderContract) {
        printf("\nThe vehicle is under a contract at the moment, please come back later\n");
        return;
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
