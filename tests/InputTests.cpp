extern "C" {
#include "../src/input.h"
}
#include "Utils.h"
#include "InputTests.h"

TEST_F(InputTests, ValidReadDataReadOption) {
    file = Utils::createInputFile("1");
    value = readOption(file);
    ASSERT_EQ(value,1);
}

TEST_F(InputTests, InvalidOptionReadOption) {
    file = Utils::createInputFile("99");
    value = readOption(file);
    EXPECT_EQ(value, -1);
}

TEST_F(InputTests, InvalidTypeReadOption) {
    file = Utils::createInputFile("test");
    value = readOption(file);
    EXPECT_EQ(value, -1);
}

TEST_F(InputTests, ValidReadInt) {
    file = Utils::createInputFile("2");
    value = readInt(file, 1, 3);
    ASSERT_EQ(value, 2);
}

TEST_F(InputTests, InvalidIntReadInt) {
    file = Utils::createInputFile("0");
    value = readInt(file, 1, 3);
    ASSERT_EQ(value, limits);
}

TEST_F(InputTests, InvalidTypeReadInt) {
    file = Utils::createInputFile("test");
    value = readInt(file, 1, 3);
    ASSERT_EQ(value,invalidType);
}

TEST_F(InputTests, ValidReadFloat) {
    file = Utils::createInputFile("2");
    value = static_cast<int>(readFloat(file, 1, 3));
    ASSERT_EQ(value, 2);
}

TEST_F(InputTests, InvalidIntReadFloat) {
    file = Utils::createInputFile("0");
    value = static_cast<int>(readFloat(file, 1, 3));
    ASSERT_EQ(value, limits);
}

TEST_F(InputTests, InvalidTypeReadFloat) {
    file = Utils::createInputFile("test");
    value = static_cast<int>(readFloat(file, 1, 3));
    ASSERT_EQ(value,invalidType);
}

TEST_F(InputTests, ShouldRemoveOneCharacterReadString) {
    file = Utils::createInputFile("test");
    char value[4];
    readString(file, value, 4, "");
    const std::string expected {"tes"};
    EXPECT_EQ(value, expected);
}

TEST_F(InputTests, ShouldRemoveNewLineReadString) {
    file = Utils::createInputFile("hello\n");
    char value[6];
    readString(file, value, 6, "");
    const std::string expected {"hello"};
    EXPECT_EQ(value, expected);
}

TEST_F(InputTests, ExpectEmptyStringReadString) {
    file = Utils::createInputFile("hello\n");
    char value[6];
    readString(file, value, 1, "");
    const std::string expected;
    EXPECT_EQ(value, expected);
}

TEST_F(InputTests, OnlyOneCharacterReadString) {
    file = Utils::createInputFile("h");
    char value[1];
    readString(file, value, 1, "");
    const std::string expected;
    EXPECT_EQ(value, expected);
}

TEST_F(InputTests, ReadDateValidDate) {
    file = Utils::createInputFile("2024\n1\n1\n");
    date date;
    readDate(file, &date);
    EXPECT_EQ(date.year, 2024);
    EXPECT_EQ(date.month, 1);
    EXPECT_EQ(date.day, 1);
}

TEST_F(InputTests, ReadDateInvalidDay) {
    file = Utils::createInputFile("2024\n1\n40\n");
    date date;
    readDate(file, &date);
    EXPECT_EQ(date.year, 2024);
    EXPECT_EQ(date.month, 1);
    EXPECT_EQ(date.day, limits);
}

TEST_F(InputTests, ReadDateInvalidDayOrdinaryYear) {
    file = Utils::createInputFile("2023\n2\n29\n");
    date date;
    readDate(file, &date);
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 2);
    EXPECT_EQ(date.day, limits);
}
