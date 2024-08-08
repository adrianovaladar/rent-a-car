#include "logger.h"
#include "constants.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    if (instance == NULL) {
        instance = (logger *) malloc(sizeof(logger));
        if (instance != NULL) {
            initializeLogger(instance);
        }
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

static void logMessage(const logger *logger, const char *text, const logLevel level, const char *file, const char *function, const int line) {
    if (!logger->initialized)
        return;
    const char *levelString = (level == Info) ? "Info" : (level == Warning) ? "Warning"
                                                                            : "Error";
    const char *fileNameUnix = strrchr(file, '/');
    const char *fileNameWindows = strrchr(file, '\\');
    const char *fileName = NULL;
    if (fileNameUnix && fileNameWindows) {
        fileName = (fileNameUnix > fileNameWindows) ? fileNameUnix : fileNameWindows;
    } else if (fileNameUnix) {
        fileName = fileNameUnix;
    } else if (fileNameWindows) {
        fileName = fileNameWindows;
    } else {
        fileName = file;
    }
    if (fileName && (*fileName == '/' || *fileName == '\\')) {
        fileName++;
    }
    fprintf(logger->file, "[%s] %s | %s:%s:%d | %s\n", levelString, getFormattedDate(), fileName, function, line, text);
    fflush(logger->file);
}

void logFormattedMessage(const logger *logger, const logLevel level, const char *file, const char *function, const int line, const char *format, ...) {
    char *message = malloc(LENGTH_LOG * sizeof(char));
    if (message == NULL) {
        fprintf(stderr, "Memory allocation failed for logging message\n");
        return;
    }
    va_list args;
    va_start(args, format);
    vsnprintf(message, LENGTH_LOG, format, args);
    va_end(args);
    logMessage(logger, message, level, file, function, line);
    free(message);
}