#ifndef INFLUXDBLPTOOL_NOTEQUALTOTIMEVALIDATOR_H
#define INFLUXDBLPTOOL_NOTEQUALTOTIMEVALIDATOR_H

#include "not_equal_to_string_validator.h"

namespace influxdblptool {

    const auto time = "time";
    using NotEqualToTimeValidator = not_equal_to_string_validator<time>;

}


#endif //INFLUXDBLPTOOL_NOTEQUALTOTIMEVALIDATOR_H
