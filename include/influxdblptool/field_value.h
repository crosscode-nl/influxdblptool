#ifndef INFLUXDBLPTOOL_FIELD_VALUE_H
#define INFLUXDBLPTOOL_FIELD_VALUE_H
#include <stdexcept>
#include "validators.h"
#include <variant>
#include "string_types.h"

namespace influxdblptool {

    namespace traits {

        template <typename T>
        struct is_acceptable_fp_base : std::false_type {};
        template<> struct is_acceptable_fp_base<double> : std::true_type {};
        template<> struct is_acceptable_fp_base<float> : std::true_type {};
        template<typename T> struct is_acceptable_fp: is_acceptable_fp_base<std::remove_cv_t<T>> {};
        template<typename T> inline constexpr bool is_acceptable_fp_v = is_acceptable_fp<T>::value;

        template <typename T>
        struct is_acceptable_int_base : std::false_type {};
        template<> struct is_acceptable_int_base<int64_t> : std::true_type {};
        template<> struct is_acceptable_int_base<int32_t> : std::true_type {};
        template<> struct is_acceptable_int_base<int16_t> : std::true_type {};
        template<> struct is_acceptable_int_base<int8_t> : std::true_type {};
        template<typename T> struct is_acceptable_int: is_acceptable_int_base<std::remove_cv_t<T>> {};
        template<typename T> inline constexpr bool is_acceptable_int_v = is_acceptable_int<T>::value;

        template <typename T>
        struct is_acceptable_uint_base : std::false_type {};
        template<> struct is_acceptable_uint_base<uint64_t> : std::true_type {};
        template<> struct is_acceptable_uint_base<uint32_t> : std::true_type {};
        template<> struct is_acceptable_uint_base<uint16_t> : std::true_type {};
        template<> struct is_acceptable_uint_base<uint8_t> : std::true_type {};
        template<typename T> struct is_acceptable_uint: is_acceptable_uint_base<std::remove_cv_t<T>> {};
        template<typename T> inline constexpr bool is_acceptable_uint_v = is_acceptable_uint<T>::value;

    }

    class field_double {
        double value_;
    public:
        explicit field_double();
        explicit field_double(double value);
        explicit field_double(float value);
        field_double(const field_double& s);
        explicit operator double() const;
        field_double& operator=(double value);
        field_double& operator=(const field_double& value);
    };

    using field_variant = std::variant<field_double,field_string_value,bool,std::uint64_t,std::int64_t>;

    class field_value  {
    private:
        field_variant field_variant_;
    public:
        field_value();
        field_value(const field_value& f) : field_variant_{f.field_variant_} {}
        field_value(field_value&& f) noexcept : field_variant_{std::move(f.field_variant_)} {}
        template<typename Type, std::enable_if_t<traits::is_acceptable_fp_v<Type>, int> = 0>
        field_value(const Type& v) : field_variant_{field_double{v}} {}
        template<typename Type, std::enable_if_t<traits::is_acceptable_int_v<Type>, int> = 0>
        explicit field_value(const Type& v) : field_variant_{int64_t{v}} {}
        template<typename Type, std::enable_if_t<traits::is_acceptable_uint_v<Type>, int> = 0>
        explicit field_value(const Type& v) : field_variant_{uint64_t{v}} {}
        explicit field_value(field_string_value v);
        explicit field_value(field_double v);
        explicit field_value(bool v);
        explicit field_value(const char* v);
        explicit field_value(std::string_view v);
        explicit field_value(std::string v);
        template<typename Type, std::enable_if_t<traits::is_acceptable_fp_v<Type>, int> = 0>
        field_value& operator=(const Type& v) {
            field_variant_ = field_double{v};
            return *this;
        }
        template<typename Type, std::enable_if_t<traits::is_acceptable_int_v<Type>, int> = 0>
        field_value& operator=(const Type& v) {
            field_variant_ = int64_t{v};
            return *this;
        }
        template<typename Type, std::enable_if_t<traits::is_acceptable_uint_v<Type>, int> = 0>
        field_value& operator=(const Type& v) {
            field_variant_ = uint64_t{v};
            return *this;
        }
        field_value& operator=(bool v);
        field_value& operator=(const field_string_value &v);
        field_value& operator=(const field_double &v);
        field_value& operator=(const char* v);
        field_value& operator=(std::string v);
        field_value& operator=(std::string_view v);
        field_value& operator=(const field_value& v);
        explicit operator const field_variant&() const;
    };

}

#endif //INFLUXDBLPTOOL_FIELD_VALUE_H
