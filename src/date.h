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
bool areDatesEqual(date date1, date date2);
bool isDateWithinRange(date start, date end, date input);
bool isDateEarlier(date date1, date date2);

#endif//RENT_A_CAR_DATE_H
