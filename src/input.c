#include "input.h"
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
}