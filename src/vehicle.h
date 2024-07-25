#ifndef RENT_A_CAR_VEHICLE_H
#define RENT_A_CAR_VEHICLE_H

#include <stdbool.h>
#include <stdio.h>

/**
 * @brief enum representing the offce locations.
 */
typedef enum office {
    Braga = 0,    /**< Office located in Braga. */
    Coimbra = 1,  /**< Office located in Coimbra. */
    Guarda = 2,   /**< Office located in Guarda. */
    Faro = 3,     /**< Office located in Faro. */
    Lisbon = 4,   /**< Office located in Lisbon. */
    Porto = 5,    /**< Office located in Porto. */
    Unknown = 6   /**< Office location is unknown. */
} office;

/**
 * @brief Structure representing a vehicle.
 */
typedef struct vehicle {
    int code;                   /**< Unique code identifying the vehicle. */
    char brand[11];             /**< Brand of the vehicle, max 10 characters plus null terminator. */
    char model[11];             /**< Model of the vehicle, max 10 characters plus null terminator. */
    char registrationPlate[7];  /**< Registration plate of the vehicle, max 6 characters plus null terminator. */
    float km;                   /**< Kilometers driven by the vehicle. */
    int location;               /**< Location identifier where the vehicle is situated. */
    bool isUnderContract;       /**< Contract status of the vehicle, true if under contract. */
} vehicle;

/**
 * @brief Inserts a new vehicle.
 *
 * @param inputFile Pointer to the file to read from.
 * @param outputFile Pointer to the file to write output.
 * @param vehicles Array of vehicles.
 * @param quantity Number of vehicles.
 */
void insertVehicle(FILE *inputFile, FILE *outputFile, vehicle *vehicles, size_t *quantity);
/**
 * @brief Displays all vehicles.
 *
 * @param outputFile Pointer to the file to write output.
 * @param vehicles Array of vehicles.
 * @param quantity Number of vehicles.
 */
void showAllVehicles(FILE *outputFile, const vehicle *vehicles, size_t quantity);
/**
 * @brief Displays a vehicle by their code and shows options for further actions.
 *
 * @param inputFile Pointer to the file to read from.
 * @param outputFile Pointer to the file to write output.
 * @param vehicles Array of vehicles.
 * @param quantity Number of vehicles.
 */
void manageVehicleByCode(FILE *inputFile, FILE *outputFile, vehicle *vehicles, size_t *quantity);
/**
 * @brief Searches for a vehicle by their code.
 *
 * @param vehicles Array of vehicles.
 * @param quantity Number of vehicles.
 * @param code Code of the vehicle to search for.
 * @return Index of the vehicle if found, -1 otherwise.
 */
int searchCodeVehicle(const vehicle *vehicles, size_t quantity, int code);
/**
 * @brief Shows the vehicle location.
 *
 * @param outputFile Pointer to the file to write output.
 * @param vehicles Array of vehicles.
 * @param quantity Number of vehicles.
 */
void showVehiclesLocation(FILE *outputFile, const vehicle *vehicles, size_t quantity);
/**
 * @brief Converts an office enumeration value to its corresponding text representation.
 *
 * @param o The office enumeration value to convert.
 */
char *officeEnumToText(enum office o);
/**
 * @brief Reads vehicles from a file.
 *
 * @param outputFile Pointer to the file to write output.
 * @param fileName Name of the file to read vehicles from.
 * @param vehicles Array to store the vehicles.
 * @param quantity Number of vehicles.
 */
void readVehicles(FILE *outputFile, const char *fileName, vehicle *vehicles, size_t *quantity);
/**
 * @brief Writes vehicles to a file.
 *
 * @param outputFile Pointer to the file to write output.
 * @param fileName Name of the file to write vehicles to.
 * @param vehicles Array of vehicles.
 * @param quantity Number of vehicles.
 */
void writeVehicles(FILE *outputFile, const char *fileName, const vehicle *vehicles, size_t quantity);

#endif//RENT_A_CAR_VEHICLE_H
