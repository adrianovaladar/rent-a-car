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


static void readCustomerData(FILE *inputFile, FILE *outputFile, customer *c) {
    readString(inputFile, outputFile, c->name, 30, "Name (maximum 30 characters): ");
    readString(inputFile, outputFile, c->address, 40, "Address (maximum 40 characters): ");
    readString(inputFile, outputFile, c->driverLicense, 10, "Driver license (maximum 10 characters): ");
}

static void setCodeNewCustomer(customer *customers, const size_t *position) {
    customers[*position].code = 0;
    for (size_t i = 0; i < *position; i++) {
        if (customers[i].code == customers[*position].code)
            customers[*position].code++;
    }
}

void insertCustomer(FILE *inputFile, FILE *outputFile, customer *customers, size_t *quantity) {
    if (*quantity == MAX_CUSTOMERS) {
        fprintf(outputFile, "We reached our full capacity of customers. Please come back later");
        return;
    }
    fprintf(outputFile, "--- Customer data ---\n");
    setCodeNewCustomer(customers, quantity);
    fprintf(outputFile, "Code: %d\n", customers[*quantity].code);
    readCustomerData(inputFile, outputFile, &customers[*quantity]);
    customers[*quantity].isRisky = 0;
    (*quantity)++;
}

static void editCustomer(FILE *inputFile, FILE *outputFile, customer *c) {
    if (c->isUnderContract) {
        fprintf(outputFile, "The customer is under a contract at the moment, please come back later\n");
        return;
    }
    fprintf(outputFile, "--- Customer data ---\n");
    readCustomerData(inputFile, outputFile, c);
}

static void deleteCustomer(FILE *outputFile, customer *customers, const int position, size_t *quantity) {
    if (customers[position].isUnderContract) {
        fprintf(outputFile, "The customer is under a contract at the moment, please come back later\n");
        return;
    }
    for (int i = position; i <= *quantity - 1; i++) {
        customers[i] = customers[i + 1];
    }
    (*quantity)--;
    fprintf(outputFile, "Customer deleted successfully\n");
}

static void showCustomer(FILE *outputFile, customer c) {
    fprintf(outputFile, "Code: %d\n", c.code);
    fprintf(outputFile, "Name: %s\n", c.name);
    fprintf(outputFile, "Address: %s\n", c.address);
    fprintf(outputFile, "Type: %s\n", c.isRisky == 0 ? "Regular" : "Risky");
    fprintf(outputFile, "Driver license: %s\n", c.driverLicense);
}

void manageCustomerByCode(FILE *inputFile, FILE *outputFile, customer *customers, size_t *quantity) {
    if (*quantity == 0) {
        fprintf(outputFile, "There are no registered customers\n");
        return;
    }
    const int n = readInt(inputFile, outputFile, 0, MAX_CUSTOMERS - 1);
    const int codeFound = searchCodeCustomer(customers, *quantity, n);
    if (codeFound >= 0) {
        showCustomer(outputFile, customers[codeFound]);
        fprintf(outputFile, "Edit(e) Delete(d) (Press any other key plus enter to leave this menu): ");
        unsigned char op;
        do {
            op = fgetc(inputFile);
        } while (op == '\n');
        if (op == 'E' || op == 'e') {
            editCustomer(inputFile, outputFile, &customers[codeFound]);
        } else if (op == 'D' || op == 'd') {
            deleteCustomer(outputFile, customers, codeFound, quantity);
        }
    } else {
        fprintf(outputFile, "No customer found with code %d\n", n);
    }
}

void showAllCustomers(FILE *outputFile, const customer *customers, const size_t quantity) {
    if (quantity == 0) {
        fprintf(outputFile, "There are no registered customers\n");
        return;
    }
    fprintf(outputFile, "--- Customer data ---\n\n");
    for (int i = 0; i < quantity; i++) {
        showCustomer(outputFile, customers[i]);
        fprintf(outputFile, "\n");
    }
}

void readCustomers(FILE *outputFile, const char *fileName, customer *customers, size_t *quantity) {
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        fprintf(outputFile, "Error opening file '%s'!\n", fileName);
        return;
    }
    // calculate the number of customers
    fseek(file, 0, SEEK_END);
    *quantity = ftell(file) / sizeof(customer);
    // set the file position back to the beginning
    rewind(file);
    // check if the number of customers is bigger than expected
    if (*quantity > MAX_CUSTOMERS) {
        fprintf(outputFile, "Error: invalid file size in '%s'\n", fileName);
        fclose(file);
        return;
    }
    // read the customers
    fread(customers, sizeof(customer), *quantity, file);
    fclose(file);
}

// function to write customers to a binary file
void writeCustomers(FILE *outputFile, const char *fileName, const customer *customers, const size_t quantity) {
    FILE *file = fopen(fileName, "wb");
    if (file == NULL) {
        fprintf(outputFile, "Error opening file '%s'!\n", fileName);
        return;
    }
    // write the customers
    fwrite(customers, sizeof(customer), quantity, file);
    fclose(file);
}
