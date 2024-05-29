#ifndef RENT_A_CAR_INPUT_H
#define RENT_A_CAR_INPUT_H

#include "date.h"
#include <stdio.h>

#ifdef TEST
const int success = 0;
const int invalidType = -1;
const int limits = -2;
#endif

int readInt(FILE *file, int lowerLimit, int upperLimit);
float readFloat(float lowerLimit, float upperLimit);
void readString(char *s, int size, char *info);
void readDate(date *date);
int readOption(FILE *file);

#endif//RENT_A_CAR_INPUT_H
