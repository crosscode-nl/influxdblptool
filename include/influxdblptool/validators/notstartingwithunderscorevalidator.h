#ifndef INFLUXDBLPTOOL_NOTSTARTINGWITHUNDERSCOREVALIDATOR_H
#define INFLUXDBLPTOOL_NOTSTARTINGWITHUNDERSCOREVALIDATOR_H
#include "influxdblptool/abstractions/ivalidator.h"

namespace influxdblptool {

    struct NotStartingWithUnderscoreValidator : public IValidator {
        void validate(std::string_view v) override;
    };

}


#endif //INFLUXDBLPTOOL_NOTSTARTINGWITHUNDERSCOREVALIDATOR_H
