#include "input.h"
#include <stdio.h>

int readInt(int lowerLimit, int upperLimit) {
    int value;
    int check;
    do {
        printf("\nInsert a number between %d and %d: ", lowerLimit, upperLimit);
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
            printf("\nOnly values between %d and %d are accepted", lowerLimit, upperLimit);
    } while (1);
    return value;
}

float readFloat(float lowerLimit, float upperLimit) {
    float value;
    int check;
    do {
        printf("\nInsert a number between %.2f and %.2f: ", lowerLimit, upperLimit);
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
            printf("\nOnly values between %.2f and %.2f are accepted", lowerLimit, upperLimit);
    } while (1);
    return value;
}

void readChars(char *s, int tam, char *info) {
    int i = 0;
    char ch;
    puts(info);
    ch = getchar();
    while (ch != '\n' && i < tam) {
        s[i] = ch;
        i++;
        ch = getchar();
    }
    s[i] = '\0';
}