extern "C" {
#include "../src/input.h"
}
#include "Utils.h"
#include "InputTests.h"

TEST_F(InputTests, ValidReadDataReadOption) {
    inputFile = Utils::createInputFile("1");
    value = readOption(inputFile, outputFile);
    ASSERT_EQ(value,1);
}

TEST_F(InputTests, InvalidOptionReadOption) {
    inputFile = Utils::createInputFile("99");
    value = readOption(inputFile, outputFile);
    EXPECT_EQ(value, -1);
}

TEST_F(InputTests, InvalidTypeReadOption) {
    inputFile = Utils::createInputFile("test");
    value = readOption(inputFile, outputFile);
    EXPECT_EQ(value, -1);
}

TEST_F(InputTests, ValidReadInt) {
    inputFile = Utils::createInputFile("2");
    value = readInt(inputFile, outputFile, 1, 3);
    ASSERT_EQ(value, 2);
}

TEST_F(InputTests, InvalidIntReadInt) {
    inputFile = Utils::createInputFile("0");
    value = readInt(inputFile, outputFile, 1, 3);
    ASSERT_EQ(value, limits);
}

TEST_F(InputTests, InvalidTypeReadInt) {
    inputFile = Utils::createInputFile("test");
    value = readInt(inputFile, outputFile, 1, 3);
    ASSERT_EQ(value,invalidType);
}

TEST_F(InputTests, ValidReadFloat) {
    inputFile = Utils::createInputFile("2");
    value = static_cast<int>(readFloat(inputFile, outputFile, 1, 3));
    ASSERT_EQ(value, 2);
}

TEST_F(InputTests, InvalidIntReadFloat) {
    inputFile = Utils::createInputFile("0");
    value = static_cast<int>(readFloat(inputFile, outputFile, 1, 3));
    ASSERT_EQ(value, limits);
}

TEST_F(InputTests, InvalidTypeReadFloat) {
    inputFile = Utils::createInputFile("test");
    value = static_cast<int>(readFloat(inputFile, outputFile, 1, 3));
    ASSERT_EQ(value,invalidType);
}

TEST_F(InputTests, ShouldRemoveOneCharacterReadString) {
    inputFile = Utils::createInputFile("test");
    char value[4];
    readString(inputFile, outputFile, value, 4, "");
    const std::string expected {"tes"};
    EXPECT_EQ(value, expected);
}

TEST_F(InputTests, ShouldRemoveNewLineReadString) {
    inputFile = Utils::createInputFile("hello\n");
    char value[6];
    readString(inputFile, outputFile, value, 6, "");
    const std::string expected {"hello"};
    EXPECT_EQ(value, expected);
}

TEST_F(InputTests, ExpectEmptyStringReadString) {
    inputFile = Utils::createInputFile("hello\n");
    char value[6];
    readString(inputFile, outputFile, value, 1, "");
    const std::string expected;
    EXPECT_EQ(value, expected);
}

TEST_F(InputTests, OnlyOneCharacterReadString) {
    inputFile = Utils::createInputFile("h");
    char value[1];
    readString(inputFile, outputFile, value, 1, "");
    const std::string expected;
    EXPECT_EQ(value, expected);
}

TEST_F(InputTests, ReadDateValidDate) {
    inputFile = Utils::createInputFile("2024\n1\n1\n");
    date date;
    readDate(inputFile, outputFile, &date);
    EXPECT_EQ(date.year, 2024);
    EXPECT_EQ(date.month, 1);
    EXPECT_EQ(date.day, 1);
}

TEST_F(InputTests, ReadDateInvalidDay) {
    inputFile = Utils::createInputFile("2024\n1\n40\n");
    date date;
    readDate(inputFile, outputFile, &date);
    EXPECT_EQ(date.year, 2024);
    EXPECT_EQ(date.month, 1);
    EXPECT_EQ(date.day, limits);
}

TEST_F(InputTests, ReadDateInvalidDayOrdinaryYear) {
    inputFile = Utils::createInputFile("2023\n2\n29\n");
    date date;
    readDate(inputFile, outputFile, &date);
    EXPECT_EQ(date.year, 2023);
    EXPECT_EQ(date.month, 2);
    EXPECT_EQ(date.day, limits);
}
