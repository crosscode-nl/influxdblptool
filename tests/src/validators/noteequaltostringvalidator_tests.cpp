#include "gtest/gtest.h"
#include "influxdblptool/validators/not_equal_to_string_validator.h"

using namespace std::literals;

const auto TIME_CASE_STR{"TIME"sv};
const auto TIME_STR{"time"sv};

TEST(NotEqualToStringValidator,ThrowsExceptionWhenEqualsToString)
{
    influxdblptool::not_equal_to_string_validator<TIME_STR> notEqualToStringValidator;
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

    influxdblptool::not_equal_to_string_validator<TIME_STR> notEqualToStringValidator;
    try {
        notEqualToStringValidator.validate("tImE");
    } catch (std::invalid_argument &e) {
        ASSERT_EQ("String argument cannot be equal to `time'"s,e.what());
        return;
    }
    FAIL();
}

TEST(NotEqualToStringValidator,ThrowsExceptionWhenEqualsToCaseMismatch2String) {
    influxdblptool::not_equal_to_string_validator<TIME_CASE_STR> notEqualToStringValidator;
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
    influxdblptool::not_equal_to_string_validator<TIME_CASE_STR> notEqualToStringValidator;
    notEqualToStringValidator.validate("nottime");
}