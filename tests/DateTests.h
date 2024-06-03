#ifndef DATETESTS_H
#define DATETESTS_H

#include <gtest/gtest.h>
extern "C" {
#include "../src/date.h"
}

class DateTests : public ::testing::Test {
protected:
    date date1{};
    date date2{};
};



#endif //DATETESTS_H
