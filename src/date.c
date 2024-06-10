#include "date.h"
#include "constants.h"
#include <stdbool.h>
#include <stdlib.h>

bool isLeapYear(const int year) {
    const bool b = (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0) ? true : false;
    return b;
}

int daysInMonth(const int month, const int year) {
    switch (month) {
        case 2:
            return isLeapYear(year) ? 29 : 28;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            return 31;
    }
}

bool isEmptyDate(const date d) {
    return d.day == 0 && d.month == 0 && d.year == 0;
}

int diffInDays(const date d1, const date d2) {
    int daysDate1 = d1.day;
    int daysDate2 = d2.day;
    for (int m = 1; m < d1.month; m++) {
        daysDate1 += daysInMonth(m, d1.year);
    }
    for (int m = 1; m < d2.month; m++) {
        daysDate2 += daysInMonth(m, d2.year);
    }
    for (int y = START_YEAR; y < d1.year; y++) {
        daysDate1 += 365 + (int)isLeapYear(y);
    }
    for (int y = START_YEAR; y < d2.year; y++) {
        daysDate2 += 365 + (int)isLeapYear(y);
    }
    return abs(daysDate2 - daysDate1);
}

bool areDatesEqual(const date d1, const date d2) {
    return d1.day == d2.day && d1.month == d2.month && d1.year == d2.year;
}

bool isDateWithinRange(const date start, const date end, const date d) {
    if (d.year < start.year || d.year > end.year) {
        return 0;
    }
    if (d.year == start.year && (d.month < start.month || (d.month == start.month && d.day < start.day))) {
        return 0;
    }
    if (d.year == end.year && (d.month > end.month || (d.month == end.month && d.day > end.day))) {
        return 0;
    }
    return 1;
}

bool isDateBefore(const date d1, const date d2) {
    return (d1.day < d2.day && d1.month == d2.month && d1.year == d2.year) || (d1.month < d2.month && d1.year == d2.year) || d1.year < d2.year;
}

bool isDateAfter(const date d1, const date d2) {
    return d1.year > d2.year || (d1.year == d2.year && d1.month > d2.month) || (d1.year == d2.year && d1.month == d2.month && d1.day > d2.day);
}
