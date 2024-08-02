#ifndef RENT_A_CAR_DATE_H
#define RENT_A_CAR_DATE_H

#include <stdbool.h>

/**
 * @brief Structure representing a date.
 */
typedef struct date {
    int day;   /**< Day of the month */
    int month; /**< Month of the year */
    int year;  /**< Year */
} date;

/**
 * @brief Determines if a given year is a leap year.
 *
 * @param year The year to check.
 * @return `true` if the year is a leap year, `false` otherwise.
 */
bool isLeapYear(int year);
/**
 * @brief Checks if a date is empty.
 *
 * An empty date is defined as having all fields set to 0.
 *
 * @param d date to check.
 * @return `true` if the date is empty, `false` otherwise.
 */
bool isEmptyDate(date d);
/**
 * @brief Calculates the difference in days between dates.
 *
 * @param d1 date for comparison.
 * @param d2 date for comparison.
 * @return The number of days between the two dates.
 */
int diffInDays(date d1, date d2);
/**
 * @brief Retrieves the number of days in a given month
 *
 * @param month Month to check.
 * @param year Year to check.
 * @return The number of days in the specified month.
 */
int daysInMonth(int month, int year);
/**
 * @brief Checks if two dates are equal.
 *
 * @param d1 Date for comparison.
 * @param d2 Date for comparison.
 * @return `true` if the dates are equal, `false` otherwise.
 */
bool areDatesEqual(date d1, date d2);
/**
 * @brief Checks if a given date is in a range.
 *
 * The range includes the start and end dates.
 *
 * @param start Beginning of the range.
 * @param end End of the range.
 * @param d Date to check.
 * @return `true` if the date is within the range, `false` otherwise.
 */
bool isDateWithinRange(date start, date end, date d);
/**
 * @brief Checks if a date is before other date.
 *
 * @param d1 Reference date.
 * @param d2 Date to be compared with.
 * @return `true` if d1 is before d2, `false` otherwise.
 */
bool isDateBefore(date d1, date d2);
/**
 * @brief Checks if a date is after other date.
 *
 * @param d1 Reference date.
 * @param d2 Date to be compared with.
 * @return `true` if d1 is after d2, `false` otherwise.
 */
bool isDateAfter(date d1, date d2);
/**
 * @brief Formats a date as a string in the format "DD/MM/YYYY".
 *
 * This function uses a static buffer to store the formatted date string.
 * Note that this function is not thread-safe because it uses a static buffer.
 *
 * @param d The date to format.
 * @return A pointer to a static buffer containing the formatted date.
 *         The buffer will be overwritten by subsequent calls to this function.
 */
char* getFormattedDate(date d);

#endif//RENT_A_CAR_DATE_H
