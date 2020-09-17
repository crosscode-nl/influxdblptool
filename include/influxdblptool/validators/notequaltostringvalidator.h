#ifndef INFLUXDBLPTOOL_NOTEQUALTOSTRINGVALIDATOR_H
#define INFLUXDBLPTOOL_NOTEQUALTOSTRINGVALIDATOR_H
#include "influxdblptool/abstractions/ivalidator.h"
#include <algorithm>
#include <stdexcept>

namespace influxdblptool {

    template<auto &str>
    struct NotEqualToStringValidator : public IValidator {
        void validate(std::string_view v) {
            std::string_view s{str};
            auto case_insensitive_char_compare = [](const auto &a, const auto &b) {
                return tolower(a)==tolower(b);
            };
            if (std::size(v)==std::size(s) && std::equal(begin(s),end(s),std::begin(v),case_insensitive_char_compare)) {
                throw std::invalid_argument(std::string{"String argument cannot be equal to `"} + std::string{s} + "'");
            }
        }
    };

}
#endif //INFLUXDBLPTOOL_NOTEQUALTOSTRINGVALIDATOR_H
