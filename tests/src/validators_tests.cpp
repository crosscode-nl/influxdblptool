#include "gtest/gtest.h"
#include "influxdblptool/validators.h"

using namespace std::literals;
using namespace influxdblptool::validators;

class MeasurementInvalidInputTest : public testing::TestWithParam<std::tuple<std::string_view,std::string>> {};
TEST_P(MeasurementInvalidInputTest,throws_on_invalid_input) {

    auto [input, expectedMsg] = GetParam();
    try {
        throw_when_measurement_invalid(input);
    } catch (std::exception &e) {
        ASSERT_EQ(expectedMsg,e.what());
        return;
    }
    FAIL();
}

INSTANTIATE_TEST_SUITE_P(
        validators,
        MeasurementInvalidInputTest,
        ::testing::Values(
                std::make_tuple("#invalid"sv,"Input must not start with hashtags, or line becomes a comment."s)
        )
);


/*
TEST(validators,throw_when_measurement_invalid_no_throw_on_valid_input {

}

void throw_when_measurement_invalid(std::string_view input);
void throw_when_tag_key_invalid(std::string_view input);
void throw_when_field_key_invalid(std::string_view input);
void throw_when_tag_value_invalid(std::string_view input);
void throw_when_field_value_invalid(std::string_view input);
 */