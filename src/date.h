#ifndef RENT_A_CAR_DATE_H
#define RENT_A_CAR_DATE_H

#include <stdbool.h>

typedef struct date {
    int day;
    int month;
    int year;
} date;

bool isEmptyDate(date d);
int diffInDays(date date1, date date2);
int daysInMonth(int month, int year);

#endif//RENT_A_CAR_DATE_H
