#include "LoggerTests.h"
#include <fstream>
#include <source_location>

using location = std::source_location;

TEST_F(LoggerTest, CheckInitialization) {
    log = getLoggerInstance();
    ASSERT_TRUE(log != nullptr);
}

TEST_F(LoggerTest, CheckLogMessage) {
    log = getLoggerInstance();
    logFormattedMessage(log, Info, location::current().file_name(), location::current().function_name(), location::current().line(), "Test message");
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
    }
    std::string line;
    bool found = false;
    while (std::getline(file, line)) {
        if (line.find("Test message") != std::string::npos) {
            found = true;
            break;
        }
    }
    ASSERT_TRUE(found);
}

TEST_F(LoggerTest, LogLevelTest) {
    log = getLoggerInstance();
    logFormattedMessage(log, Info, location::current().file_name(), location::current().function_name(), location::current().line(), "Test message");
    logFormattedMessage(log, Error, location::current().file_name(), location::current().function_name(), location::current().line(), "Error message");
    logFormattedMessage(log, Warning, location::current().file_name(), location::current().function_name(), location::current().line(), "Warning message");
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Unable to open file: " << fileName << std::endl;
    }
    std::string line;
    int testCount{};
    int errorCount{};
    int warningCount{};
    while (std::getline(file, line)) {
        if (line.find("Test message") != std::string::npos) {
            testCount++;
        } else if (line.find("Error message") != std::string::npos) {
            errorCount++;
        } else if (line.find("Warning message") != std::string::npos) {
            warningCount++;
        }
    }
    ASSERT_GT(testCount, 0);
    ASSERT_GT(errorCount, 0);
    ASSERT_GT(warningCount, 0);
}
