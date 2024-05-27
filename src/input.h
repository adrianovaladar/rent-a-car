#ifndef RENT_A_CAR_INPUT_H
#define RENT_A_CAR_INPUT_H

#include "date.h"
#include <stdio.h>

int readInt(int lowerLimit, int upperLimit);
float readFloat(float lowerLimit, float upperLimit);
void readString(char *s, int size, char *info);
void readDate(date *date);
int readOption(FILE *file);

#endif//RENT_A_CAR_INPUT_H
