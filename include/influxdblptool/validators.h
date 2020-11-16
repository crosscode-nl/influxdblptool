#ifndef INFLUXDBLPTOOL_VALIDATORS_H
#define INFLUXDBLPTOOL_VALIDATORS_H
#include <string_view>
#include <stdexcept>


namespace crosscode::influxdblptool {

    class validator_exception : public std::invalid_argument {
        using std::invalid_argument::invalid_argument;
    };

    /// The validators namespace contains all validators. It is internally used by this library.
    namespace validators {

        /// Will validate a string_view and throws an validator exception when:
        /// * string is empty
        /// * string starts with an underscore
        /// * string is equal to keyword: time
        /// * string contains a newline character
        /// * string length exceeds 64kb
        /// * string starts with an hash symbol
        /// \param input The string_view to validate.
        void throw_when_measurement_invalid(std::string_view input);

        /// Will validate a string_view and throws an validator exception when:
        /// * string is empty
        /// * string starts with an underscore
        /// * string is equal to keyword: time
        /// * string contains a newline character
        /// * string length exceeds 64kb
        /// \param input The string_view to validate.
        void throw_when_tag_key_invalid(std::string_view input);

        /// Will validate a string_view and throws an validator exception when:
        /// * string is empty
        /// * string starts with an underscore
        /// * string is equal to keyword: time
        /// * string contains a newline character
        /// * string length exceeds 64kb
        /// \param input The string_view to validate.
        void throw_when_field_key_invalid(std::string_view input);

        /// Will validate a string_view and throws an validator exception when:
        /// * string contains a newline character
        /// * string length exceeds 64kb
        /// \param input The string_view to validate.
        void throw_when_tag_value_invalid(std::string_view input);

        /// Will validate a string_view and throws an validator exception when:
        /// * string contains a newline character
        /// * string length exceeds 64kb
        /// \param input The string_view to validate.
        void throw_when_field_string_value_invalid(std::string_view input);

        /// Will validate a double and throws an validator exception when:
        /// * double has an infinite value
        /// * double is not a number.
        /// \param input The double to validate.
        void throw_when_double_value_invalid(double value);

    }

}

#endif //INFLUXDBLPTOOL_VALIDATORS_H
