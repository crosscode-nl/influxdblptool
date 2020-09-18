#ifndef INFLUXDBLPTOOL_VALIDATOR_AGGREGATE_H
#define INFLUXDBLPTOOL_VALIDATOR_AGGREGATE_H
#include "influxdblptool/abstractions/ivalidator.h"

namespace influxdblptool {

    template <typename ...TValidator>
    struct validator_aggregate : public IValidator {
        static_assert((std::is_base_of<IValidator,TValidator>::value && ...),"All template arguments must inherit from IValidator.");
        static_assert((std::is_default_constructible<TValidator>::value && ...),"All template arguments must be default constructable.");
        void validate(std::string_view v) const override {
            (TValidator{}.validate(v),...);
        }
    };

}


#endif //INFLUXDBLPTOOL_VALIDATOR_AGGREGATE_H
