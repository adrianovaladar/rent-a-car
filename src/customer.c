#include "customer.h"
#include "constants.h"
#include "input.h"
#include <stdio.h>

int searchCodeCustomer(customer customers[], size_t quantity, int code) {
    int i, position = -1;

    for (i = 0; i <= quantity && position == -1; i++)
        if (customers[i].code == code)
            position = i;

    return position;
}


static void readCustomerData(customer *c) {
    readString(c->name, 30, "Name (maximum 30 characters):");
    readString(c->address, 40, "Address (maximum 40 characters):");
    readString(c->driverLicense, 10, "Driver license (maximum 10 characters):");
}

static void setCodeNewCustomer(customer customers[], size_t *quantity) {
    customers[*quantity].code = 0;
    for (size_t i = 0; i < *quantity; i++) {
        if (customers[i].code == customers[*quantity].code)
            customers[*quantity].code++;
    }
}

void insertCustomer(customer customers[], size_t *quantity) {
    int n, position;

    if (*quantity == MAX_CUSTOMERS) {
        printf("We reached our full capacity of customers. Please come back later");
        return;
    }
    printf("\n--- Customer data ---\n");
    setCodeNewCustomer(customers, quantity);
    printf("Code: %d\n", customers[*quantity].code);
    customers[*quantity].code = n;
    readCustomerData(&customers[*quantity]);
    customers[*quantity].type = 0;
    (*quantity)++;
}

static void editCustomer(customer *c) {
    if (c->isUnderContract) {
        printf("\nThe customer is under a contract at the moment, please come back later\n");
        return;
    }
    printf("\n--- Customer data ---\n");
    readCustomerData(c);
}

static void deleteCustomer(customer customers[], int position, size_t *quantity) {
    if (customers[position].isUnderContract) {
        printf("\nThe customer is under a contract at the moment, please come back later\n");
        return;
    }
    int i;
    for (i = position; i <= *quantity; i++) {
        customers[i] = customers[i + 1];
    }
    (*quantity)--;
}

static void showCustomer(customer c) {
    printf("\n--- Customer data ---\n");
    printf("\n Code: %d", c.code);
    printf("\n Name: %s", c.name);
    printf("\n Address: %s", c.address);
    printf("\n Type: %s", c.type == 0 ? "Regular" : "Risky");
    printf("\n Driver license: %s\n", c.driverLicense);
}

void showCustomerByCodeAndShowOptions(customer customers[], size_t quantity) {
    int n, codeFound;

    if (quantity == 0) {
        printf("\nThere are no registered customers\n");
        return;
    }
    n = readInt(1000, 9999);
    codeFound = searchCodeCustomer(customers, quantity, n);
    if (codeFound >= 0) {
        showCustomer(customers[codeFound]);
        printf("\nEdit(e) Delete(d) (Press any other key plus enter to leave this menu)\n");
        unsigned char op;
        do {
            op = getchar();
        } while (op == '\n');
        if (op == 'E' || op == 'e') {
            editCustomer(&customers[codeFound]);
        } else if (op == 'D' || op == 'd') {
            deleteCustomer(customers, codeFound, &quantity);
            printf("Customer deleted successfully\n");
        }
    } else {
        printf("No customer found with code %d\n", n);
    }
}

void showAllCustomers(customer customers[], size_t quantity) {
    int i;
    if (quantity == 0) {
        printf("\nThere are no registered customers\n");
        return;
    }
    for (i = 0; i < quantity; i++) {
        showCustomer(customers[i]);
    }
}
