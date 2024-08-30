#include "input.h"
#include "constants.h"
#include "date.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

#ifdef TEST
const int invalidType = -1;
const int limits = -2;
#endif

static void flushInput(FILE *inputFile, int check) {
    while ((check = fgetc(inputFile)) != '\n' && check != EOF) {
        // flush file
    }
}

int readInt(FILE *inputFile, FILE *outputFile, const int lowerLimit, const int upperLimit) {
    int value;
    int check;
    do {
        fprintf(outputFile, "Insert a number between %d and %d: ", lowerLimit, upperLimit);
        check = fscanf(inputFile, "%d", &value);
        if (check != 1) {
#ifdef TEST
            return invalidType;
#endif
            flushInput(inputFile, check);
            continue;
        }
        if (value >= lowerLimit && value <= upperLimit)
            break;
        fprintf(outputFile, "Only values between %d and %d are accepted\n", lowerLimit, upperLimit);
#ifdef TEST
        return limits;
#endif
    } while (1);
    flushInput(inputFile, check);
    return value;
}

float readFloat(FILE *inputFile, FILE *outputFile, const float lowerLimit, const float upperLimit) {
    float value;
    int check;
    do {
        fprintf(outputFile, "Insert a number between %.2f and %.2f: ", lowerLimit, upperLimit);
        check = fscanf(inputFile, "%f", &value);
        if (check != 1) {
#ifdef TEST
            return (float)invalidType;
#endif
            flushInput(inputFile, check);
            continue;
        }
        if (value >= lowerLimit - EPSILON && value <= upperLimit + EPSILON)
            break;
        fprintf(outputFile, "Only values between %.2f and %.2f are accepted\n", lowerLimit, upperLimit);
#ifdef TEST
        return (float)limits;
#endif
    } while (1);
    flushInput(inputFile, check);
    return value;
}

void readString(FILE *inputFile, FILE *outputFile, char *s, const int size, const char *info) {
    if (size <= 0)
        return;
    fprintf(outputFile, "%s", info);
    bool isStringRead = false;
    while (!isStringRead) {
        if (fgets(s, size, inputFile) != NULL) {
            s[strcspn(s, "\n")] = '\0';
            if (strlen(s) > 0) {
                isStringRead = true;
            }
        } else {
            s[0] = '\0';
            isStringRead = true;
        }
#ifdef TEST
        if (strlen(s) == 0)
            break;
#endif
    }
}

void readDate(FILE *inputFile, FILE *outputFile, date *date) {
    fprintf(outputFile, "Insert the year\n");
    date->year = readInt(inputFile, outputFile, START_YEAR, INT_MAX);
    fprintf(outputFile, "Insert the month\n");
    date->month = readInt(inputFile, outputFile, 1, 12);
    const int numberOfDays = daysInMonth(date->month, date->year);
    fprintf(outputFile, "Month of %d days\n", numberOfDays);
    date->day = readInt(inputFile, outputFile, 1, numberOfDays);
}

int readOption(FILE *inputFile, FILE *outputFile) {
    int option;
    bool optionExists;
    int check;
    do {
        fprintf(outputFile, "Insert an option: ");
        check = fscanf(inputFile, "%d", &option);
        optionExists = option == 0 || option == 1 || option == 2 || option == 3 ||
                       option == 11 || option == 12 || option == 13 || option == 14 ||
                       option == 21 || option == 22 || option == 23;
        if (check != 1 || !optionExists) {
            fprintf(outputFile, "Input not valid\n");
#ifdef TEST
            return -1;
#endif
            while ((check = fgetc(inputFile)) != '\n' && check != EOF) {
                // flush file
            }
        }
    } while (!optionExists);
    flushInput(inputFile, check);
    return option;
}
