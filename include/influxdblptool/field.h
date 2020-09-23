#ifndef INFLUXDBLPTOOL_FIELD_H
#define INFLUXDBLPTOOL_FIELD_H
#include <stdexcept>
#include "validators.h"
#include <variant>
#include "string_types.h"
#include "abstractions/serializable.h"

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
        template<> struct is_acceptable_int_base<int32_t> : std::true_type {};
        template<> struct is_acceptable_int_base<int16_t> : std::true_type {};
        template<> struct is_acceptable_int_base<int8_t> : std::true_type {};
        template<typename T> struct is_acceptable_int: is_acceptable_int_base<std::remove_cv_t<T>> {};
        template<typename T> inline constexpr bool is_acceptable_int_v = is_acceptable_int<T>::value;

        template <typename T>
        struct is_acceptable_uint_base : std::false_type {};
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
        field_double(const field_double &s);
        explicit operator double() const;
        field_double &operator=(double value);
        field_double &operator=(const field_double &value);
    };

    using field_variant = std::variant<field_double,field_string_value,bool,std::uint64_t,std::int64_t>;

    class field : public field_variant, public abstractions::serializable {
    public:
        using field_variant::field_variant;
        using field_variant::operator=;
        field(const field& f) : field_variant{f} {}
        field(field&& f) noexcept : field_variant{std::move(f)} {}
        template<typename Type, std::enable_if_t<traits::is_acceptable_fp_v<Type>, int> = 0>
        field(const Type& v) : field_variant{field_double{v}} {}
        template<typename Type, std::enable_if_t<traits::is_acceptable_int_v<Type>, int> = 0>
        explicit field(const Type& v) : field_variant{int64_t{v}} {}
        template<typename Type, std::enable_if_t<traits::is_acceptable_uint_v<Type>, int> = 0>
        explicit field(const Type& v) : field_variant{uint64_t{v}} {}
        explicit field(const char* v);
        explicit field(std::string_view v);
        explicit field(std::string v);
        template<typename Type, std::enable_if_t<traits::is_acceptable_fp_v<Type>, int> = 0>
        field& operator=(const Type& v) {
            *(this) = field_double{v};
            return *this;
        }
        template<typename Type, std::enable_if_t<traits::is_acceptable_int_v<Type>, int> = 0>
        field& operator=(const Type& v) {
            *(this) = int64_t{v};
            return *this;
        }
        template<typename Type, std::enable_if_t<traits::is_acceptable_uint_v<Type>, int> = 0>
        field& operator=(const Type& v) {
            *(this) = uint64_t{v};
            return *this;
        }
        field& operator=(const char* v);
        field& operator=(std::string v);
        field& operator=(std::string_view v);
        field& operator=(const field &v);
        void serialize(std::ostream &s) const override;
    };

}

#endif //INFLUXDBLPTOOL_FIELD_H
