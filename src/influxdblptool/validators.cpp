#include "influxdblptool/validators.h"
#include <algorithm>
#include <cmath>

namespace influxdblptool::validators {

    using namespace std::literals;
    using namespace influxdblptool;

    void throw_when_empty(std::string_view input) {
        if (empty(input)) throw validator_exception("Input must not be empty.");
    }

    void throw_when_starts_with_underscore(std::string_view input) {
        if (input.substr(0,1)=="_"sv) throw validator_exception("Input must not start with underscore.");
    }

    void throw_when_starts_with_hashtag(std::string_view input) {
        if (input.substr(0,1)=="#"sv) throw validator_exception("Input must not start with hashtags.");
    }

    bool case_insensitive_char_compare(const char& a, const char& b) {
        return tolower(a)==tolower(b);
    }

    void throw_when_equals_to_time(std::string_view input) {
        std::string_view s{"time"};
        if (std::size(input)==std::size(s) && std::equal(begin(s),end(s),std::begin(input),case_insensitive_char_compare)) {
            throw validator_exception("Input must not be equal to `time'");
        }
    }

    void throw_when_length_exceeds_64KB(std::string_view input) {
        using size_t = std::string_view::size_type;
        const size_t KB = 1024;
        const size_t LIMIT = 64*KB;
        if (size(input)>=LIMIT) throw validator_exception("Input must be <64KB");
    }

    bool is_new_line(const char& c) {
        return c=='\n';
    }

    void throw_when_contains_new_line_char(std::string_view input) {
        if (std::any_of(begin(input),end(input),is_new_line)) {
            throw validator_exception("Input must not contain new line character '\\n'");
        }
    }

    void throw_when_key_invalid(std::string_view input) {
        throw_when_empty(input);
        throw_when_starts_with_underscore(input);
        throw_when_equals_to_time(input);
        throw_when_contains_new_line_char(input);
        throw_when_length_exceeds_64KB(input);
    }

    void throw_when_measurement_invalid(std::string_view input) {
        throw_when_key_invalid(input);
        throw_when_starts_with_hashtag(input);
    }

    void throw_when_tag_key_invalid(std::string_view input) {
        throw_when_key_invalid(input);
    }

    void throw_when_field_key_invalid(std::string_view input) {
        throw_when_key_invalid(input);
    }

    void throw_when_field_invalid(std::string_view input) {
        throw_when_contains_new_line_char(input);
        throw_when_length_exceeds_64KB(input);
    }

    void throw_when_field_string_value_invalid(std::string_view input) {
        throw_when_field_invalid(input);
    }

    void throw_when_tag_value_invalid(std::string_view input) {
        throw_when_field_invalid(input);
    }

    void throw_when_double_value_invalid(double value) {
        if (std::isnan(value)) throw validator_exception("NaN value not allowed.");
        if (std::isinf(value)) throw validator_exception("Infinite value not allowed.");
    }



    // TODO: Test how influxDB behaves when # not at start of line.
    // TODO: Test how influxDB behaves with \n in keys. Maybe it is allowed?

}