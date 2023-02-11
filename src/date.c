#include "date.h"
#include "constants.h"
#include <stdbool.h>
#include <stdlib.h>

static bool isLeapYear(int year) {
    bool b = (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0) ? true : false;
    return b;
}

int daysInMonth(int month, int year) {
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

bool isEmptyDate(date d) {
    return d.day == 0 && d.month == 0 && d.year == 0;
}

int diffInDays(date date1, date date2) {
    int daysDate1 = date1.day;
    int daysDate2 = date2.day;
    for (int m = 1; m < date1.month; m++) {
        daysDate1 += daysInMonth(m, date1.year);
    }
    for (int m = 1; m < date2.month; m++) {
        daysDate2 += daysInMonth(m, date2.year);
    }
    for (int y = START_YEAR; y < date1.year; y++) {
        daysDate1 += 365 + isLeapYear(y);
    }
    for (int y = START_YEAR; y < date2.year; y++) {
        daysDate2 += 365 + isLeapYear(y);
    }
    return abs(daysDate2 - daysDate1);
}

bool areDatesEqual(date date1, date date2) {
    return date1.day == date2.day && date1.month == date2.month && date1.year == date2.year;
}

bool isDateWithinRange(date start, date end, date input) {
    if (input.year < start.year || input.year > end.year) {
        return 0;
    }
    if (input.year == start.year && (input.month < start.month || (input.month == start.month && input.day < start.day))) {
        return 0;
    }
    if (input.year == end.year && (input.month > end.month || (input.month == end.month && input.day > end.day))) {
        return 0;
    }
    return 1;
}

bool isDateEarlier(date date1, date date2) {
    return (date1.day > date2.day && date1.month == date2.month && date1.year == date2.year) || (date1.month > date2.month && date1.year == date2.year) || date1.year > date2.year;
}
