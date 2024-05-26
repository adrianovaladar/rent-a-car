#ifndef RENT_A_CAR_INPUT_H
#define RENT_A_CAR_INPUT_H

#include "date.h"

int readInt(int lowerLimit, int upperLimit);
float readFloat(float lowerLimit, float upperLimit);
void readString(char *s, int size, char *info);
void readDate(date *date);
int readOption();

#endif//RENT_A_CAR_INPUT_H
