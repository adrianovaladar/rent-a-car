#include "DateTests.h"
extern "C" {
#include "../src/date.h"
}

date setDate(const int d, const int m, const int y) {
    date date;
    date.day = d;
    date.month = m;
    date.year = y;
    return date;
}

TEST(isLeapYear, ExpectTrue) {
    constexpr int year = 2024;
    EXPECT_EQ(isLeapYear(year), true);
}

TEST(isLeapYear, ExpectFalse) {
    constexpr int year = 2023;
    EXPECT_EQ(isLeapYear(year), false);
}

TEST(DaysInMonth, DaysInMonthCommonYear) {
    EXPECT_EQ(daysInMonth(1, 2023), 31);
    EXPECT_EQ(daysInMonth(2, 2023), 28);
    EXPECT_EQ(daysInMonth(3, 2023), 31);
    EXPECT_EQ(daysInMonth(4, 2023), 30);
    EXPECT_EQ(daysInMonth(5, 2023), 31);
    EXPECT_EQ(daysInMonth(6, 2023), 30);
    EXPECT_EQ(daysInMonth(7, 2023), 31);
    EXPECT_EQ(daysInMonth(8, 2023), 31);
    EXPECT_EQ(daysInMonth(9, 2023), 30);
    EXPECT_EQ(daysInMonth(10, 2023), 31);
    EXPECT_EQ(daysInMonth(11, 2023), 30);
    EXPECT_EQ(daysInMonth(12, 2023), 31);
}

TEST(DaysInMonth, LeapYear) {
    EXPECT_EQ(daysInMonth(1, 2024), 31);
    EXPECT_EQ(daysInMonth(2, 2024), 29);
    EXPECT_EQ(daysInMonth(3, 2024), 31);
    EXPECT_EQ(daysInMonth(4, 2024), 30);
    EXPECT_EQ(daysInMonth(5, 2024), 31);
    EXPECT_EQ(daysInMonth(6, 2024), 30);
    EXPECT_EQ(daysInMonth(7, 2024), 31);
    EXPECT_EQ(daysInMonth(8, 2024), 31);
    EXPECT_EQ(daysInMonth(9, 2024), 30);
    EXPECT_EQ(daysInMonth(10, 2024), 31);
    EXPECT_EQ(daysInMonth(11, 2024), 30);
    EXPECT_EQ(daysInMonth(12, 2024), 31);
}

TEST_F(DateTests, DiffInDaysSameDate) {
    date1 = setDate(1, 1, 2020);
    date2 = setDate(1, 1, 2020);
    EXPECT_EQ(diffInDays(date1, date2), 0);
}

TEST_F(DateTests, DiffInDaysDifferentDatesSameYear) {
    date1 = setDate(1, 1, 2020);
    date2 = setDate(31, 12, 2020);
    EXPECT_EQ(diffInDays(date1, date2), 365);
}

TEST_F(DateTests, DiffInDaysDifferentDatesLeapYear) {
    date1 = setDate(1, 1, 2020);
    date2 = setDate(1, 1, 2021);
    EXPECT_EQ(diffInDays(date1, date2), 366);
}

TEST_F(DateTests, DiffInDaysAcrossYears) {
    date1 = setDate(31, 12, 2020);
    date2 = setDate(1, 1, 2022);
    EXPECT_EQ(diffInDays(date1, date2), 366);
}

TEST_F(DateTests, DiffInDaysSameMonthDifferentYear) {
    date1 = setDate(15, 6, 2020);
    date2 = setDate(15, 6, 2022);
    EXPECT_EQ(diffInDays(date1, date2), 730);
}

TEST_F(DateTests, AreDatesEqualSameDates) {
    date1 = setDate(1, 1, 2024);
    date2 = setDate(1, 1, 2024);
    EXPECT_EQ(areDatesEqual(date1, date2), true);
}

TEST_F(DateTests, AreDatesEqualDifferentDay) {
    date1 = setDate(1, 1, 2024);
    date2 = setDate(2, 1, 2024);
    EXPECT_EQ(areDatesEqual(date1, date2), false);
}

TEST_F(DateTests, AreDatesEqualDifferentMonth) {
    date1 = setDate(1, 1, 2024);
    date2 = setDate(1, 2, 2024);
    EXPECT_EQ(areDatesEqual(date1, date2), false);
}

TEST_F(DateTests, AreDatesEqualDifferentYear) {
    date1 = setDate(1, 1, 2024);
    date2 = setDate(1, 1, 2023);
    EXPECT_EQ(areDatesEqual(date1, date2), false);
}
