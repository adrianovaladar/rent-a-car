#ifndef LOGGER_H
#define LOGGER_H

/**
 * @brief Enumeration for log levels.
 */
typedef enum logLevel {
    Info,    /**< Informational message. */
    Warning, /**< Warning message. */
    Error    /**< Error message. */
} logLevel;

typedef struct logger logger;

/**
 * @brief Gets the singleton instance of the logger.
 *
 * @return A pointer to the logger instance.
 */
logger *getLoggerInstance();
/**
 * @brief Converts a log level to its corresponding text representation.
 *
 * @param l The log level.
 * @return A string representing the log level.
 */
char *logLevelToText(logLevel l);
/**
 * @brief Logs a message to the logger.
 *
 * @param logger The logger instance.
 * @param text The message to log.
 * @param level The log level of the message.
 * @param file The name of the file from which the log will be generated.
 * @param function The name of the function from which the log will be generated.
 * @param line The line number from which the log will be generated.
 */
void logMessage(const logger *logger, const char *text, logLevel level, const char *file, const char *function, int line);

#endif// LOGGER_H
