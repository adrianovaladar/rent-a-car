#include "customer.h"
#include "constants.h"
#include "input.h"
#include <stdio.h>

int searchCodeCustomer(const customer *customers, const size_t quantity, const int code) {
    int position = -1;
    int i = 0;
    while (i <= quantity && position == -1) {
        if (customers[i].code == code)
            position = i;
        i++;
    }
    return position;
}


static void readCustomerData(FILE *file, customer *c) {
    readString(file, c->name, 30, "Name (maximum 30 characters): ");
    readString(file, c->address, 40, "Address (maximum 40 characters): ");
    readString(file, c->driverLicense, 10, "Driver license (maximum 10 characters): ");
}

static void setCodeNewCustomer(customer *customers, const size_t *position) {
    customers[*position].code = 0;
    for (size_t i = 0; i < *position; i++) {
        if (customers[i].code == customers[*position].code)
            customers[*position].code++;
    }
}

void insertCustomer(FILE *file, customer *customers, size_t *quantity) {
    if (*quantity == MAX_CUSTOMERS) {
        printf("We reached our full capacity of customers. Please come back later");
        return;
    }
    printf("--- Customer data ---\n");
    setCodeNewCustomer(customers, quantity);
    printf("Code: %d\n", customers[*quantity].code);
    readCustomerData(file, &customers[*quantity]);
    customers[*quantity].isRisky = 0;
    (*quantity)++;
}

static void editCustomer(FILE *file, customer *c) {
    if (c->isUnderContract) {
        printf("The customer is under a contract at the moment, please come back later\n");
        return;
    }
    printf("--- Customer data ---\n");
    readCustomerData(file, c);
}

static void deleteCustomer(customer *customers, const int position, size_t *quantity) {
    if (customers[position].isUnderContract) {
        printf("The customer is under a contract at the moment, please come back later\n");
        return;
    }
    for (int i = position; i <= *quantity - 1; i++) {
        customers[i] = customers[i + 1];
    }
    (*quantity)--;
    printf("Customer deleted successfully\n");
}

static void showCustomer(customer c) {
    printf("Code: %d\n", c.code);
    printf("Name: %s\n", c.name);
    printf("Address: %s\n", c.address);
    printf("Type: %s\n", c.isRisky == 0 ? "Regular" : "Risky");
    printf("Driver license: %s\n", c.driverLicense);
}

void manageCustomerByCode(FILE *file, customer *customers, size_t *quantity) {
    if (*quantity == 0) {
        printf("There are no registered customers\n");
        return;
    }
    const int n = readInt(file, 0, MAX_CUSTOMERS - 1);
    const int codeFound = searchCodeCustomer(customers, *quantity, n);
    if (codeFound >= 0) {
        showCustomer(customers[codeFound]);
        printf("Edit(e) Delete(d) (Press any other key plus enter to leave this menu): ");
        unsigned char op;
        do {
            op = fgetc(file);
        } while (op == '\n');
        if (op == 'E' || op == 'e') {
            editCustomer(file, &customers[codeFound]);
        } else if (op == 'D' || op == 'd') {
            deleteCustomer(customers, codeFound, quantity);
        }
    } else {
        printf("No customer found with code %d\n", n);
    }
}

void showAllCustomers(const customer *customers, const size_t quantity) {
    if (quantity == 0) {
        printf("There are no registered customers\n");
        return;
    }
    printf("--- Customer data ---\n\n");
    for (int i = 0; i < quantity; i++) {
        showCustomer(customers[i]);
        printf("\n");
    }
}

void readCustomers(const char *fileName, customer *customers, size_t *quantity) {
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        printf("Error opening file '%s'!\n", fileName);
        return;
    }
    // calculate the number of customers
    fseek(file, 0, SEEK_END);
    *quantity = ftell(file) / sizeof(customer);
    // set the file position back to the beginning
    rewind(file);
    // check if the number of customers is bigger than expected
    if (*quantity > MAX_CUSTOMERS) {
        printf("Error: invalid file size in '%s'\n", fileName);
        fclose(file);
        return;
    }
    // read the customers
    fread(customers, sizeof(customer), *quantity, file);
    fclose(file);
}

// function to write customers to a binary file
void writeCustomers(const char *fileName, const customer *customers, const size_t quantity) {
    FILE *file = fopen(fileName, "wb");
    if (file == NULL) {
        printf("Error opening file '%s'!\n", fileName);
        return;
    }
    // write the customers
    fwrite(customers, sizeof(customer), quantity, file);
    fclose(file);
}
