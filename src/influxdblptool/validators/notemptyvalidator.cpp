#include "influxdblptool/validators/notemptyvalidator.h"
#include <stdexcept>

namespace influxdblptool {

    void NotEmptyValidator::validate(std::string_view v) {
        if (v.empty()) throw std::invalid_argument("String argument cannot be empty.");
    }

}