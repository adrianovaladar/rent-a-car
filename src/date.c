#include "date.h"
#include "input.h"
#include <stdbool.h>
#include <stdio.h>

void validateDate(date *date) {
    int month, year, day;
    printf("Insert the year");
    year = readInt(1950, 2050);
    printf("Insert the month");
    month = readInt(1, 12);
    if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12)) {
        printf("Month of 31 days");
        day = readInt(1, 31);
    } else {
        if (month == 2) {
            if (isLeapYear(year)) {
                printf("Month of 29 days");
                day = readInt(1, 29);
            } else {
                printf("Month de 28 days");
                day = readInt(1, 28);
            }
        } else {
            printf("Month de 30 dias");
            day = readInt(1, 30);
        }
    }
    date->day = day;
    date->month = month;
    date->year = year;
}

bool isLeapYear(int year) {
    bool b = (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0) ? true : false;
    return b;
}

bool isEmptyDate(date d) {
    return d.day == 0 && d.month == 0 && d.year == 0;
}
