#include "customer.h"
#include "constants.h"
#include "input.h"
#include <stdio.h>

int searchCodeClient(customer cli[], int qtd, int cod) {
    int i, position = -1;

    for (i = 0; i <= qtd && position == -1; i++)
        if (cli[i].code == cod)
            position = i;

    return position;
}


void readCustomerData(customer *c) {
    readString(c->name, 30, "Name (maximum 30 characters):");
    readString(c->address, 40, "Address (maximum 40 characters):");
    readString(c->driverLicense, 10, "Driver license (maximum 10 characters):");// check behaviour
}

void insertCustomer(customer cli[], int *qtd) {
    int n, position;

    if (*qtd == MAX_CLI) {
        printf("We reached our full capacity of contracts. Please come back later");
        return;
    }
    printf("\n--- Customer data ---\n");
    do {
        printf("Code");
        n = readInt(1000, 9999);
        position = searchCodeClient(cli, *qtd, n);
        if (position != -1) {
            printf("This code is already taken. Please insert another one\n");
        }
    } while (position >= 0);
    cli[*qtd].code = n;
    readCustomerData(&cli[*qtd]);
    cli[*qtd].type = 0;
    (*qtd)++;
}

void editCustomer(customer c[], int pos) {
    if (c[pos].isUnderContract) {
        printf("\nThe customer is under a contract at the moment, please come back later\n");
        return;
    }
    printf("\n--- Customer data ---\n");
    readCustomerData(&c[pos]);
}

void deleteCustomer(customer c[], int pos, int *qtd) {
    if (c[pos].isUnderContract) {
        printf("\nThe customer is under a contract at the moment, please come back later\n");
        return;
    }
    int i;
    for (i = pos; i <= *qtd; i++) {
        c[i] = c[i + 1];
    }
    (*qtd)--;
}

void showCustomer(customer c) {
    printf("\n--- Customer data ---\n");
    printf("\n Code: %d", c.code);
    printf("\n Name: %s", c.name);
    printf("\n Address: %s", c.address);
    printf("\n Type: %s", c.type == 0 ? "Regular" : "Risky");
    printf("\n Driver license: %s\n", c.driverLicense);
}

void showCustomerByCode(customer c[], int qtd) {
    int n, codeFound;

    if (qtd == 0) {
        printf("\nThere are no registered customers\n");
        return;
    }
    n = readInt(1000, 9999);
    codeFound = searchCodeClient(c, qtd, n);
    if (codeFound >= 0) {
        showCustomer(c[codeFound]);
        printf("\nEdit(e) Delete(d) (Press any other key plus enter to leave this menu)\n");
        unsigned char op;
        do {
            op = getchar();
        } while (op == '\n');
        if (op == 'E' || op == 'e') {
            editCustomer(c, codeFound);
        } else if (op == 'D' || op == 'd') {
            deleteCustomer(c, codeFound, &qtd);
        }
    } else {
        printf("\nNo customer found with code %d\n", n);
    }
}

void showAllCustomers(customer c[], int qtd) {
    int i;
    if (qtd == 0) {
        printf("\nThere are no registered customers\n");
        return;
    }
    for (i = 0; i < qtd; i++) {
        showCustomer(c[i]);
    }
}
