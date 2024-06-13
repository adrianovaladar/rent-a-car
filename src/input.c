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

int readInt(FILE *file, const int lowerLimit, const int upperLimit) {
    int value;
    do {
        printf("Insert a number between %d and %d: ", lowerLimit, upperLimit);
        int check = fscanf(file, "%d", &value);
        if (check != 1) {
#ifdef TEST
            return invalidType;
#endif
            while ((check = fgetc(file)) != '\n' && check != EOF) {
                // flush file
            }
            continue;
        }
        if (value >= lowerLimit && value <= upperLimit)
            break;
        printf("Only values between %d and %d are accepted\n", lowerLimit, upperLimit);
#ifdef TEST
        return limits;
#endif
    } while (1);
    return value;
}

float readFloat(FILE *file, const float lowerLimit, const float upperLimit) {
    float value;
    do {
        printf("Insert a number between %.2f and %.2f: ", lowerLimit, upperLimit);
        int check = fscanf(file, "%f", &value);
        if (check != 1) {
#ifdef TEST
            return (float)invalidType;
#endif
            while ((check = fgetc(file)) != '\n' && check != EOF) {
                // flush file
            }
            continue;
        }
        if (value >= lowerLimit - EPSILON && value <= upperLimit + EPSILON)
            break;
        printf("Only values between %.2f and %.2f are accepted\n", lowerLimit, upperLimit);
#ifdef TEST
        return (float)limits;
#endif
    } while (1);
    return value;
}

void readString(FILE *file, char *s, const int size, const char *info) {
    if (size <= 0)
        return;
    printf("%s", info);
    while (1) {
        if (fgets(s, size, file) == NULL) {
            s[0] = '\0';
            break;
        }
        s[strcspn(s, "\n")] = '\0';
        if (strlen(s) > 0) {
            break;
        }
#ifdef TEST
        if (strlen(s) == 0)
            break;
#endif
    }
}

void readDate(FILE *file, date *date) {
    printf("Insert the year\n");
    date->year = readInt(file, START_YEAR, INT_MAX);
    printf("Insert the month\n");
    date->month = readInt(file, 1, 12);
    const int numberOfDays = daysInMonth(date->month, date->year);
    printf("Month of %d days\n", numberOfDays);
    date->day = readInt(file, 1, numberOfDays);
}

int readOption(FILE *file) {
    int option;
    bool optionExists;
    do {
        printf("Insert an option: ");
        int check = fscanf(file, "%d", &option);
        optionExists = option == 0 || option == 1 || option == 2 || option == 3 ||
                       option == 11 || option == 12 || option == 13 || option == 14 ||
                       option == 21 || option == 22 || option == 23;
        if (check != 1 || !optionExists) {
            printf("Input not valid\n");
#ifdef TEST
            return -1;
#endif
            while ((check = fgetc(file)) != '\n' && check != EOF) {
                // flush file
            }
        }
    } while (!optionExists);
    return option;
}
