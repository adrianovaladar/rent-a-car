#include "Utils.h"
#include <cstdio>

FILE *Utils::createInputFile(const char* str) {
    FILE *file = tmpfile();
    fputs(str, file);
    rewind(file);
    return file;
}
