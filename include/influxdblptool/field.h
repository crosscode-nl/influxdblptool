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
        field_double &operator=(const field_double &value);
    };

    using field_variant = std::variant<field_double,field_string_value,bool,std::uint64_t,std::int64_t>;



    // TODO: template this
    class field : public field_variant, public abstractions::serializable {
    public:
        using field_variant::field_variant;
        using field_variant::operator=;
        field(const field &f);
        field(field &&f) noexcept;
        explicit field(const double &v);
        explicit field(const float &v);
        explicit field(const int32_t &v);
        explicit field(const int16_t &v);
        explicit field(const int8_t &v);
        explicit field(const uint32_t &v);
        explicit field(const uint16_t &v);
        explicit field(const uint8_t &v);
        explicit field(const char* v);
        explicit field(std::string v);
        explicit field(std::string_view v);
        field& operator=(const double &v);
        field& operator=(const float &v);
        field& operator=(const int32_t &v);
        field& operator=(const int16_t &v);
        field& operator=(const int8_t &v);
        field& operator=(const uint32_t &v);
        field& operator=(const uint16_t &v);
        field& operator=(const uint8_t &v);
        field& operator=(const char* v);
        field& operator=(std::string v);
        field& operator=(std::string_view v);
        field& operator=(const field &v);
        void serialize(std::ostream &s) const override;
    };
}




#endif //INFLUXDBLPTOOL_FIELD_H
