#include "gtest/gtest.h"
#include "influxdblptool/validators/notemptyvalidator.h"

using namespace std::literals;
/*
TEST(NotEmptyValidator,NoExceptionWhenStringNotEmpty)
{
    influxdblptool::NotEmptyValidator notEmptyValidator;
    notEmptyValidator.validate("s"sv);
}

TEST(NotEmptyValidator,ExceptionWhenStringIsEmpty)
{
    influxdblptool::NotEmptyValidator notEmptyValidator;
    try {
        notEmptyValidator.validate(""sv);
    } catch (std::invalid_argument &e) {
        ASSERT_EQ("String argument cannot be empty."s,e.what());
        return;
    }
    FAIL();
}*/