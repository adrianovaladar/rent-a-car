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
 * @param file Pointer to the file to read from.
 * @param lowerLimit The lower limit for the integer value.
 * @param upperLimit The upper limit for the integer value.
 * @return The integer read from the file, or, in case of tests, a return code.
 */
int readInt(FILE *file, int lowerLimit, int upperLimit);
/**
 * @brief Reads a float from a file within specified limits.
 *
 * @param file Pointer to the file to read from.
 * @param lowerLimit The lower limit for the float value.
 * @param upperLimit The upper limit for the float value.
 * @return The float read from the file, or, in case of tests, a return code.
 */
float readFloat(FILE *file, float lowerLimit, float upperLimit);
/**
 * @brief Reads a string from a file.
 *
 * @param file Pointer to the file to read from.
 * @param s Pointer to the buffer where the string will be stored.
 * @param size The maximum size of the string to be read.
 * @param info Information for the user.
 */
void readString(FILE *file, char *s, int size, const char *info);
/**
 * @brief Reads a date.
 *
 * @param file Pointer to the file to read from.
 * @param date Pointer to the date structure to be populated.
 */
void readDate(FILE *file, date *date);
/**
 * @brief Reads an option from a file.
 *
 * @param file Pointer to the file to read from.
 * @return The option selected by the user.
 */
int readOption(FILE *file);

#endif//RENT_A_CAR_INPUT_H
