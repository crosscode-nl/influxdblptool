#include "gtest/gtest.h"
/*
#include "influxdblptool/validators/notstartingwithunderscorevalidator.h"

using namespace std::literals;

TEST(NotStartingWithUnderscoreValidator,NoExceptionWhenStringDoesNotStartWithUnderscore)
{
    influxdblptool::NotStartingWithUnderscoreValidator notStartingWithUnderscoreValidator;
    notStartingWithUnderscoreValidator.validate("s_"sv);
}

TEST(NotStartingWithUnderscoreValidator,ExceptionWhenStringStartsWithUnderscore)
{
    influxdblptool::NotStartingWithUnderscoreValidator notStartingWithUnderscoreValidator;
    try {
        notStartingWithUnderscoreValidator.validate("_s"sv);
    } catch (std::invalid_argument &e) {
        ASSERT_EQ("String argument cannot start with an underscore."s,e.what());
        return;
    }
    FAIL();
}
 */