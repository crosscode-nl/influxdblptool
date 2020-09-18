#ifndef INFLUXDBLPTOOL_KEYVALIDATOR_H
#define INFLUXDBLPTOOL_KEYVALIDATOR_H
#include "validator_aggregate.h"
#include "notequaltotimevalidator.h"
#include "notemptyvalidator.h"
#include "notstartingwithunderscorevalidator.h"

namespace influxdblptool {

    using KeyValidator = validator_aggregate<NotEmptyValidator, NotStartingWithUnderscoreValidator, NotEqualToTimeValidator>;
    using TagKeyValidator = KeyValidator;
    using FieldKeyValidator = KeyValidator;

}

#endif //INFLUXDBLPTOOL_KEYVALIDATOR_H
