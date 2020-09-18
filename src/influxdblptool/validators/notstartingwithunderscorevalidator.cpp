#include "influxdblptool/validators/notstartingwithunderscorevalidator.h"
#include <stdexcept>

namespace influxdblptool {
    using namespace std::literals;

    void NotStartingWithUnderscoreValidator::validate(std::string_view v) const {
        if (v.substr(0,1)=="_"sv) throw std::invalid_argument("String argument cannot start with an underscore.");
    }

}

