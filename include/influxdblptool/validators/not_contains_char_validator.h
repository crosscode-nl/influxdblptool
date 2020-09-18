#ifndef INFLUXDBLPTOOL_NOT_CONTAINS_CHAR_VALIDATOR_H
#define INFLUXDBLPTOOL_NOT_CONTAINS_CHAR_VALIDATOR_H
#include "influxdblptool/abstractions/ivalidator.h"
#include <algorithm>
#include <stdexcept>

namespace influxdblptool {
    using namespace std::literals;

    template <char matchCharacter, auto& description>
    struct not_contains_char_validator : public IValidator {
        static_assert(std::is_constructible<std::string, decltype(description)>::value,"Cannot construct a std::string with template argument description.");
        void validate(std::string_view v) const override {
            char tc = matchCharacter;
            auto is_char = [m=tc](const char &c){
                return c==m;
            };
            if (std::any_of(std::begin(v),std::end(v),is_char)) {
                throw std::invalid_argument("String argument contains invalid character: "s + std::string{description});
            }
        }
    };

}



#endif //INFLUXDBLPTOOL_NOTEMPTYVALIDATOR_H
