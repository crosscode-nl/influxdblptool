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

    template<class T>
    constexpr auto is_allowed_as_int64_t() {
        return std::is_same<int32_t,T>::value && std::is_same<int64_t,T>::value && std::is_same<int16_t,T>::value && std::is_same<int8_t,T>::value;
    }

    template<class T>
    constexpr auto is_allowed_as_uint64_t(){
        return std::is_same<uint32_t,T>::value && std::is_same<uint64_t,T>::value && std::is_same<uint16_t,T>::value && std::is_same<uint8_t,T>::value;
    }


    class field : public field_variant, public abstractions::serializable {
    public:
        using field_variant::field_variant;
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
        void serialize(std::ostream &s) const override;
    };
}




#endif //INFLUXDBLPTOOL_FIELD_H
