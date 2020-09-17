#include "gtest/gtest.h"
#include "influxdblptool/validators/notequaltostringvalidator.h"

using namespace std::literals;

const char TIME_STR[]{"time"};
const char TIME_CASE_STR[]{"TIME"};

TEST(NotEqualToStringValidatorTests,NotEqualToStringValidatorThrowsExceptionWhenEqualsToString)
{
    influxdblptool::NotEqualToStringValidator<TIME_STR> notEqualToStringValidator;
    try {
        notEqualToStringValidator.validate("time");
    } catch (std::invalid_argument &e) {
        ASSERT_EQ("String argument cannot be equal to `time'"s,e.what());
        return;
    }
    FAIL();
}

TEST(NotEqualToStringValidatorTests,NotEqualToStringValidatorThrowsExceptionWhenEqualsToCaseMismatch1String)
{
    influxdblptool::NotEqualToStringValidator<TIME_STR> notEqualToStringValidator;
    try {
        notEqualToStringValidator.validate("tImE");
    } catch (std::invalid_argument &e) {
        ASSERT_EQ("String argument cannot be equal to `time'"s,e.what());
        return;
    }
    FAIL();
}

TEST(NotEqualToStringValidatorTests,NotEqualToStringValidatorThrowsExceptionWhenEqualsToCaseMismatch2String) {
    influxdblptool::NotEqualToStringValidator<TIME_CASE_STR> notEqualToStringValidator;
    try {
        notEqualToStringValidator.validate("time");
    } catch (std::invalid_argument &e) {
        ASSERT_EQ("String argument cannot be equal to `TIME'"s, e.what());
        return;
    }
    FAIL();
}

TEST(NotEqualToStringValidatorTests,NotEqualToStringValidatorDoesNoThrowWhenValuesAreDifferent)
{
    influxdblptool::NotEqualToStringValidator<TIME_CASE_STR> notEqualToStringValidator;
    notEqualToStringValidator.validate("nottime");
}