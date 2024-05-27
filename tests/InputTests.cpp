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

TEST_F(InputTests, validReadData) {
    file = createInputFile("1");
    option = readOption(file);
    ASSERT_EQ(option,1);
}

TEST_F(InputTests, InvalidOption) {
    file = createInputFile("99");
    option = readOption(file);
    EXPECT_EQ(option, -1);
}

TEST_F(InputTests, InvalidType) {
    file = createInputFile("test");
    option = readOption(file);
    EXPECT_EQ(option, -1);
}
