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
    ASSERT_EQ(value, 0);
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
