#ifndef LOGGERTESTS_H
#define LOGGERTESTS_H

extern "C" {
#include "../src/logger.h"
}
#include <gtest/gtest.h>

inline std::string getDate() {
    const auto now = std::chrono::system_clock::now();
    const auto nowTime = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm{};
    localtime_r(&nowTime, &now_tm);
    std::stringstream ss;
    ss << std::put_time(&now_tm, "%Y-%m-%d");
    return ss.str();
}

class LoggerTest : public ::testing::Test {
protected:
    logger *log{};
    std::string fileName;
    void SetUp() override {
        fileName = "logs/log_" + getDate() + ".txt";
    }
};


#endif//LOGGERTESTS_H
