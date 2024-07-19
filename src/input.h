#ifndef RENT_A_CAR_INPUT_H
#define RENT_A_CAR_INPUT_H

#include "date.h"
#include <stdio.h>

#ifdef TEST
/// Invalid type return code
extern const int invalidType;
/// Limits exceeded return code
extern const int limits;
#endif

/**
 * @brief Reads an integer from a file within specified limits.
 *
 * @param inputFile Pointer to the file to read from.
 * @param outputFile
 * @param lowerLimit The lower limit for the integer value.
 * @param upperLimit The upper limit for the integer value.
 * @return The integer read from the file, or, in case of tests, a return code.
 */
int readInt(FILE *inputFile, FILE *outputFile, int lowerLimit, int upperLimit);
/**
 * @brief Reads a float from a file within specified limits.
 *
 * @param inputFile Pointer to the file to read from.
 * @param outputFile
 * @param lowerLimit The lower limit for the float value.
 * @param upperLimit The upper limit for the float value.
 * @return The float read from the file, or, in case of tests, a return code.
 */
float readFloat(FILE *inputFile, FILE *outputFile, float lowerLimit, float upperLimit);
/**
 * @brief Reads a string from a file.
 *
 * @param inputFile Pointer to the file to read from.
 * @param outputFile
 * @param s Pointer to the buffer where the string will be stored.
 * @param size The maximum size of the string to be read.
 * @param info Information for the user.
 */
void readString(FILE *inputFile, FILE *outputFile, char *s, int size, const char *info);
/**
 * @brief Reads a date.
 *
 * @param inputFile Pointer to the file to read from.
 * @param outputFile
 * @param date Pointer to the date structure to be populated.
 */
void readDate(FILE *inputFile, FILE *outputFile, date *date);
/**
 * @brief Reads an option from a file.
 *
 * @param inputFile Pointer to the file to read from.
 * @param outputFile
 * @return The option selected by the user.
 */
int readOption(FILE *inputFile, FILE *outputFile);

#endif//RENT_A_CAR_INPUT_H
