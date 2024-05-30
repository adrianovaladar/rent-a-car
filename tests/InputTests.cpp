extern "C" {
#include "../src/input.h"
}


#include "InputTests.h"

FILE * createInputFile(const char* str) {
    FILE *file = tmpfile();
    fputs(str, file);
    rewind(file);
    return file;
}

TEST_F(InputTests, validReadDataReadOption) {
    file = createInputFile("1");
    value = readOption(file);
    ASSERT_EQ(value,1);
}

TEST_F(InputTests, InvalidOptionReadOption) {
    file = createInputFile("99");
    value = readOption(file);
    EXPECT_EQ(value, -1);
}

TEST_F(InputTests, InvalidTypeReadOption) {
    file = createInputFile("test");
    value = readOption(file);
    EXPECT_EQ(value, -1);
}

TEST_F(InputTests, validReadInt) {
    file = createInputFile("2");
    value = readInt(file, 1, 3);
    ASSERT_EQ(value, success);
}

TEST_F(InputTests, invalidIntReadInt) {
    file = createInputFile("0");
    value = readInt(file, 1, 3);
    ASSERT_EQ(value, limits);
}

TEST_F(InputTests, invalidTypeReadInt) {
    file = createInputFile("test");
    value = readInt(file, 1, 3);
    ASSERT_EQ(value,invalidType);
}

TEST_F(InputTests, validReadFloat) {
    file = createInputFile("2");
    value = static_cast<int>(readFloat(file, 1, 3));
    ASSERT_EQ(value, success);
}

TEST_F(InputTests, invalidIntReadFloat) {
    file = createInputFile("0");
    value = static_cast<int>(readFloat(file, 1, 3));
    ASSERT_EQ(value, limits);
}

TEST_F(InputTests, invalidTypeReadFloat) {
    file = createInputFile("test");
    value = static_cast<int>(readFloat(file, 1, 3));
    ASSERT_EQ(value,invalidType);
}

TEST_F(InputTests, ShouldRemoveOneCharacterReadString) {
    file = createInputFile("test");
    char value[4];
    readString(file, value, 4, "");
    const std::string expected {"tes"};
    EXPECT_EQ(value, expected);
}

TEST_F(InputTests, ShouldRemoveNewLineReadString) {
    file = createInputFile("hello\n");
    char value[6];
    readString(file, value, 6, "");
    const std::string expected {"hello"};
    EXPECT_EQ(value, expected);
}

TEST_F(InputTests, ExpectEmptyStringReadString) {
    file = createInputFile("hello\n");
    char value[6];
    readString(file, value, 1, "");
    const std::string expected;
    EXPECT_EQ(value, expected);
}

TEST_F(InputTests, OnlyOneCharacterReadString) {
    file = createInputFile("h");
    char value[1];
    readString(file, value, 1, "");
    const std::string expected;
    EXPECT_EQ(value, expected);
}
