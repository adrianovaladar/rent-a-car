#include "input.h"
#include "constants.h"
#include "date.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

int readInt(int lowerLimit, int upperLimit) {
    int value;
    int check;
    do {
        printf("Insert a number between %d and %d: ", lowerLimit, upperLimit);
        check = scanf("%d", &value);
        if (check != 1) {
            while ((check = fgetc(stdin)) != '\n' && check != EOF) {
                // flush stdin
            }
            continue;
        }
        if (value >= lowerLimit && value <= upperLimit)
            break;
        else
            printf("Only values between %d and %d are accepted\n", lowerLimit, upperLimit);
    } while (1);
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
    date->year = readInt(START_YEAR, INT_MAX);
    printf("Insert the month\n");
    date->month = readInt(1, 12);
    int numberOfDays = daysInMonth(date->month, date->year);
    printf("Month of %d days\n", numberOfDays);
    date->day = readInt(1, numberOfDays);
}
