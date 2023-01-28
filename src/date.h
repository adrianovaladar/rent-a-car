#ifndef RENT_A_CAR_DATE_H
#define RENT_A_CAR_DATE_H

#include <stdbool.h>

typedef struct date {
    int day;
    int month;
    int year;
} date;

void validateDate(date *date);
bool isLeapYear(int year);
bool isEmptyDate(date d);

#endif//RENT_A_CAR_DATE_H
