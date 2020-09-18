#ifndef INFLUXDBLPTOOL_NOTEMPTYVALIDATOR_H
#define INFLUXDBLPTOOL_NOTEMPTYVALIDATOR_H
#include "influxdblptool/abstractions/ivalidator.h"

namespace influxdblptool {

    struct NotEmptyValidator : public IValidator {
        void validate(std::string_view v) const override;
    };

}


#endif //INFLUXDBLPTOOL_NOTEMPTYVALIDATOR_H
