#include "input.h"
#include "constants.h"
#include "date.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

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
#ifdef TEST
    return success;
#endif
    return value;
}

float readFloat(float lowerLimit, float upperLimit) {
    float value;
    int check;
    do {
        printf("Insert a number between %.2f and %.2f: ", lowerLimit, upperLimit);
        check = scanf("%f", &value);
        if (check != 1) {
            while ((check = fgetc(stdin)) != '\n' && check != EOF) {
                // flush stdin
            }
            continue;
        }
        if (value >= lowerLimit && value <= upperLimit)
            break;
        else
            printf("Only values between %.2f and %.2f are accepted\n", lowerLimit, upperLimit);
    } while (1);
    return value;
}

void readString(char *s, int size, char *info) {
    if (size <= 0)
        return;
    printf("%s", info);
    do {
        fgets(s, size, stdin);
    } while (strlen(s) == 1);
    s[strcspn(s, "\n")] = '\0';
}

void readDate(date *date) {
    printf("Insert the year\n");
    date->year = readInt(stdin, START_YEAR, INT_MAX);
    printf("Insert the month\n");
    date->month = readInt(stdin, 1, 12);
    int numberOfDays = daysInMonth(date->month, date->year);
    printf("Month of %d days\n", numberOfDays);
    date->day = readInt(stdin, 1, numberOfDays);
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
