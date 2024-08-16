#ifndef RENT_A_CAR_CONTRACT_H
#define RENT_A_CAR_CONTRACT_H

#include "customer.h"
#include "date.h"
#include "vehicle.h"

/**
 * @brief Structure to store information about a rental contract.
 */
typedef struct contract {
    int codeVehicle;    /**< Unique code identifying the vehicle */
    int codeCustomer;   /**< Unique code identifying the customer */
    float priceDay;     /**< Price per day of the rental */
    float quantityKm;   /**< Quantity of kilometers the vehicle did during the rental */
    date startDate;     /**< Start date of the rental */
    date endDate;       /**< End date of the rental */
    int startOffice;    /**< Code of the office where the rental starts */
    int endOffice;      /**< Code of the office where the rental ends */
    float price;        /**< Total price of the rental */
} contract;

/**
 * @brief Displays the list of rental contracts.
 *
 * @param outputFile Pointer to the file to write output.
 * @param contracts Array of contracts to be displayed.
 * @param quantity Number of contracts in the array.
 */
void showContracts(FILE *outputFile, const contract *contracts, size_t quantity);

/**
 * @brief Starts a new rental contract.
 *
 * @param inputFile Pointer to the file to read from.
 * @param outputFile Pointer to the file to write output.
 * @param logger Pointer to the logger instance used for logging messages.
 * @param contracts Array of contracts.
 * @param customers Array of customers.
 * @param vehicles Array of vehicles.
 * @param quantityContracts Number of contracts.
 * @param quantityCustomers Number of customers in the array.
 * @param quantityVehicles Number of vehicles in the array.
 */
void startContract(FILE *inputFile, FILE *outputFile, logger *logger, contract *contracts, customer *customers, vehicle *vehicles, size_t *quantityContracts, size_t quantityCustomers, size_t quantityVehicles);

/**
 * @brief Manages an existing contract by vehicle code and start date.
 *
 * @param inputFile Pointer to the file to read from.
 * @param outputFile Pointer to the file to write output.
 * @param logger Pointer to the logger instance used for logging messages.
 * @param contracts Array of contracts.
 * @param vehicles Array of vehicles.
 * @param customers Array of customers.
 * @param quantityContracts Number of contracts.
 * @param quantityVehicles Number of vehicles in the array.
 * @param quantityCustomers Number of customers in the array.
 */
void manageContractByVehicleCodeAndStartDate(FILE *inputFile, FILE *outputFile, const logger *logger, contract *contracts, vehicle *vehicles, customer *customers, size_t *quantityContracts, size_t quantityVehicles, size_t quantityCustomers);

/**
 * @brief Reads the contracts from a file.
 *
 * @param outputFile Pointer to the file to write output.
 * @param logger Pointer to the logger instance used for logging messages.
 * @param fileName Name of the file to read contracts from.
 * @param contracts Array to store the read contracts.
 * @param quantity Pointer to store the number of contracts read.
 */
void readContracts(FILE *outputFile, const logger *logger, const char *fileName, contract *contracts, size_t *quantity);

/**
 * @brief Writes the contracts to a file.
 *
 * @param outputFile Pointer to the file to write output.
 * @param logger Pointer to the logger instance used for logging messages.
 * @param fileName Name of the file to write contracts to.
 * @param contracts Array of contracts to be written.
 * @param quantity Number of contracts in the array.
 */
void writeContracts(FILE *outputFile, const logger *logger, const char *fileName, const contract *contracts, size_t quantity);

#endif//RENT_A_CAR_CONTRACT_H
