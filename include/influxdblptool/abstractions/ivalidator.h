#ifndef INFLUXDBLPTOOL_IVALIDATOR_H
#define INFLUXDBLPTOOL_IVALIDATOR_H
#include <string_view>

namespace influxdblptool {

    struct IValidator {
        virtual void validate(std::string_view v) const = 0;
    };

}

#endif //INFLUXDBLPTOOL_IVALIDATOR_H
