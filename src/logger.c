#include "logger.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <direct.h>
#define MKDIR(x) _mkdir(x)
#else
#include <unistd.h>
#define MKDIR(x) mkdir(x, 0755)
#endif

/**
 * @brief Structure representing the logger.
 */
typedef struct logger {
    FILE *file;       /**< File pointer for the log file. */
    bool initialized; /**< Indicates whether the logger is initialized. */
} logger;

static char *getFormattedDate() {
    static char buffer[20];
    const time_t now = time(NULL);
    struct tm nowTm;
    localtime_r(&now, &nowTm);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &nowTm);
    return buffer;
}

static void initializeLogger(logger *logger) {
    MKDIR("logs");
    char fileName[256];
    sprintf(fileName, "logs/log_%s.txt", getFormattedDate());
    logger->file = fopen(fileName, "a");
    if (logger->file == NULL) {
        logger->initialized = false;
        return;
    }
    logger->initialized = true;
}

logger *getLoggerInstance() {
    static logger *instance = NULL;
    instance = (logger *) malloc(sizeof(logger));
    if (instance != NULL) {
        initializeLogger(instance);
    }
    return instance;
}

char *logLevelToText(const logLevel l) {
    if (l == Info)
        return "Info\0";
    if (l == Warning)
        return "Warning\0";
    if (l == Error)
        return "Error\0";
    return "Invalid\0";
}

void logMessage(const logger *logger, const char *text, const logLevel level, const char *file, const char *function, const int line) {
    if (!logger->initialized)
        return;
    const char *levelString = (level == Info) ? "Info" : (level == Warning) ? "Warning"
                                                                            : "Error";
    fprintf(logger->file, "[%s] %s | %s:%s:%d | %s\n", levelString, getFormattedDate(), file, function, line, text);
    fflush(logger->file);
}
