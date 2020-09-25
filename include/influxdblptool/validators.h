#ifndef INFLUXDBLPTOOL_VALIDATORS_H
#define INFLUXDBLPTOOL_VALIDATORS_H
#include <string_view>
#include <stdexcept>


namespace influxdblptool {
    class validator_exception : public std::invalid_argument {
        using std::invalid_argument::invalid_argument;
    };
    namespace validators {
        void throw_when_measurement_invalid(std::string_view input);
        void throw_when_tag_key_invalid(std::string_view input);
        void throw_when_field_key_invalid(std::string_view input);
        void throw_when_tag_value_invalid(std::string_view input);
        void throw_when_field_string_value_invalid(std::string_view input);
        void throw_when_double_value_invalid(const double& value);
    }
}

#endif //INFLUXDBLPTOOL_VALIDATORS_H
