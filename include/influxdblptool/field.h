#ifndef INFLUXDBLPTOOL_FIELD_H
#define INFLUXDBLPTOOL_FIELD_H
#include <stdexcept>
#include "validators.h"
#include <variant>
#include "string_types.h"
#include "abstractions/serializable.h"

namespace influxdblptool {

    class field_double {
        double value_;
    public:
        explicit field_double();
        explicit field_double(double value);
        explicit field_double(float value);
        field_double(const field_double &s);
        explicit operator double() const;
        field_double &operator=(double value);
    };

    using field_variant = std::variant<field_double,field_string_value,bool,std::uint64_t,std::int64_t>;

    class field : public field_variant, public abstractions::serializable {
    public:
        using field_variant::field_variant;
        void serialize(std::ostream &s) const override;
    };
}




#endif //INFLUXDBLPTOOL_FIELD_H
