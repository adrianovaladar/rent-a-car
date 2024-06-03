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

TEST_F(DateTests, isLeapYearExpectTrue) {
    constexpr int year = 2024;
    EXPECT_EQ(isLeapYear(year), true);
}

TEST_F(DateTests, isLeapYearExpectFalse) {
    constexpr int year = 2023;
    EXPECT_EQ(isLeapYear(year), false);
}
