#ifndef RENT_A_CAR_CUSTOMER_H
#define RENT_A_CAR_CUSTOMER_H

#include <glob.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * @brief Structure representing a date.
 */
typedef struct customer {
    int code;/**< Code of the customer. Should be unique. */
    char name[30];/**< Name of the customer. */
    char address[40];/**< Address of the customer */
    bool isRisky; /**< Indicates if the customer is considered risky. */
    char driverLicense[11]; /**< Driver's license number of the customer. */
    bool isUnderContract; /**< Indicates if the customer is currently under contract. */
} customer;

/**
 * @brief Inserts a new customer.
 *
 * @param file Pointer to the file to read from.
 * @param customers Array of customers.
 * @param quantity Number of customers.
 */
void insertCustomer(FILE *file, customer *customers, size_t *quantity);
/**
 * @brief Displays a customer by their code and shows options for further actions.
 *
 * @param file Pointer to the file to read from.
 * @param customers Array of customers.
 * @param quantity Number of customers.
 */
void manageCustomerByCode(FILE *file, customer *customers, size_t *quantity);
/**
 * @brief Displays all customers.
 *
 * @param customers Array of customers.
 * @param quantity Number of customers.
 */
void showAllCustomers(const customer *customers, size_t quantity);
/**
 * @brief Searches for a customer by their code.
 *
 * @param customers Array of customers.
 * @param quantity Number of customers.
 * @param code Code of the customer to search for.
 * @return Index of the customer if found, -1 otherwise.
 */
int searchCodeCustomer(const customer *customers, size_t quantity, int code);
/**
 * @brief Reads customers from a file.
 *
 * @param fileName Name of the file to read customers from.
 * @param customers Array to store the customers.
 * @param quantity Number of customers.
 */
void readCustomers(const char *fileName, customer *customers, size_t *quantity);
/**
 * @brief Writes customers to a file.
 *
 * @param fileName Name of the file to write customers to.
 * @param customers Array of customers.
 * @param quantity Number of customers.
 */
void writeCustomers(const char *fileName, const customer *customers, size_t quantity);

#endif//RENT_A_CAR_CUSTOMER_H
