#ifndef INFLUXDBLPTOOL_NOTCONTAINSNEWLINEVALIDATOR_H
#define INFLUXDBLPTOOL_NOTCONTAINSNEWLINEVALIDATOR_H

#include "not_contains_char_validator.h"

namespace influxdblptool {

    const auto newline_description = "newline '\\n'";
    using NotContainsNewLineValidator = not_contains_char_validator<'\n',newline_description>;

}

#endif //INFLUXDBLPTOOL_NOTCONTAINSNEWLINEVALIDATOR_H
