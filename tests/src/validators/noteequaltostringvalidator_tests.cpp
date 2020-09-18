#include "gtest/gtest.h"
#include "influxdblptool/validators/notequaltostringvalidator.h"

using namespace std::literals;

const auto TIME_CASE_STR{"TIME"sv};
const auto TIME_STR{"time"sv};

TEST(NotEqualToStringValidator,ThrowsExceptionWhenEqualsToString)
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

TEST(NotEqualToStringValidator,ThrowsExceptionWhenEqualsToCaseMismatch1String)
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

TEST(NotEqualToStringValidator,ThrowsExceptionWhenEqualsToCaseMismatch2String) {
    influxdblptool::NotEqualToStringValidator<TIME_CASE_STR> notEqualToStringValidator;
    try {
        notEqualToStringValidator.validate("time");
    } catch (std::invalid_argument &e) {
        ASSERT_EQ("String argument cannot be equal to `TIME'"s, e.what());
        return;
    }
    FAIL();
}

TEST(NotEqualToStringValidator,DoesNotThrowWhenValuesAreDifferent)
{
    influxdblptool::NotEqualToStringValidator<TIME_CASE_STR> notEqualToStringValidator;
    notEqualToStringValidator.validate("nottime");
}