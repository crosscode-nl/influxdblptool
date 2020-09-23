#ifndef INFLUXDBLPTOOL_FIELD_H
#define INFLUXDBLPTOOL_FIELD_H
#include <stdexcept>
#include "validators.h"
#include <variant>
#include "string_types.h"
#include "abstractions/serializable.h"

namespace influxdblptool {

    namespace intern {

        template <typename Type>
        constexpr bool is_fp_to_accept =
                std::is_same<double,Type>::value ||
                std::is_same<float,Type>::value;

        template <typename Type>
        constexpr bool is_int_to_accept =
                std::is_same<int32_t,Type>::value ||
                std::is_same<int16_t,Type>::value ||
                std::is_same<int8_t,Type>::value;

        template <typename Type>
        constexpr bool is_uint_to_accept =
                std::is_same<uint32_t,Type>::value ||
                std::is_same<uint16_t,Type>::value ||
                std::is_same<uint8_t,Type>::value;
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
        template<typename Type, std::enable_if_t<intern::is_fp_to_accept<Type>, int> = 0>
        field(const Type& v) : field_variant{field_double{v}} {}
        template<typename Type, std::enable_if_t<intern::is_int_to_accept<Type>, int> = 0>
        explicit field(const Type& v) : field_variant{int64_t{v}} {}
        template<typename Type, std::enable_if_t<intern::is_uint_to_accept<Type>, int> = 0>
        explicit field(const Type& v) : field_variant{uint64_t{v}} {}
        explicit field(const char* v);
        explicit field(std::string_view v);
        explicit field(std::string v);
        template<typename Type, std::enable_if_t<intern::is_fp_to_accept<Type>, int> = 0>
        field& operator=(const Type& v) {
            *(this) = field_double{v};
            return *this;
        }
        template<typename Type, std::enable_if_t<intern::is_int_to_accept<Type>, int> = 0>
        field& operator=(const Type& v) {
            *(this) = int64_t{v};
            return *this;
        }
        template<typename Type, std::enable_if_t<intern::is_uint_to_accept<Type>, int> = 0>
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
