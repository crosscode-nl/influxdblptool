#ifndef INFLUXDBLPTOOL_VALIDATED_SERIALIZABLE_STRING_H
#define INFLUXDBLPTOOL_VALIDATED_SERIALIZABLE_STRING_H
#include <string>
#include "influxdblptool/abstractions/serializable.h"
#include "influxdblptool/validators.h"
#include "influxdblptool/escapers.h"

namespace influxdblptool {
    namespace intern {

        template <auto throw_when_invalid, auto escape>
        class validated_serializable_string : public influxdblptool::abstractions::serializable {
            std::string value_;
        public:
            explicit validated_serializable_string(std::string_view input) : value_{input} {
                throw_when_invalid(value_);
            }

            explicit validated_serializable_string(const char *input) : value_{input} {
                throw_when_invalid(value_);
            }

            explicit validated_serializable_string(std::string input) : value_{std::move(input)} {
                throw_when_invalid(value_);
            }

            validated_serializable_string(const validated_serializable_string<throw_when_invalid,escape> &input) : value_{input.value_} {
                throw_when_invalid(value_);
            }

            validated_serializable_string(validated_serializable_string<throw_when_invalid,escape> &&input) : value_{
                std::move(input.value_)} {
                throw_when_invalid(value_);
            }

            validated_serializable_string<throw_when_invalid,escape> &operator=(std::string s) {
                value_ = std::move(s);
                throw_when_invalid(value_);
                return *this;
            }

            explicit operator std::string() const {
                return value_;
            }

            explicit operator std::string_view() const {
                return value_;
            }

            const std::string &operator*() const {
                return value_;
            }

            void serialize(std::ostream &s) const override {
                s << escape(value_);
            }

            bool operator<(const validated_serializable_string<throw_when_invalid,escape>&rhs) const {
                return value_<rhs.value_;
            }

            bool operator>(const validated_serializable_string<throw_when_invalid,escape>&rhs) const {
                return value_>rhs.value_;
            }

            bool operator==(const validated_serializable_string<throw_when_invalid,escape>&rhs) const {
                return value_==rhs.value_;
            }

            bool operator!=(const validated_serializable_string<throw_when_invalid,escape>&rhs) const {
                return value_!=rhs.value_;
            }
            validated_serializable_string<throw_when_invalid,escape>& operator=(validated_serializable_string<throw_when_invalid,escape> rhs) {
                value_ = std::move(rhs.value_);
                return *this;
            }
        };
    }

    using tag_key = intern::validated_serializable_string<validators::throw_when_tag_key_invalid,escapers::escape_tag_key>;
    using tag_value = intern::validated_serializable_string<validators::throw_when_tag_value_invalid,escapers::escape_tag_value>;
    using field_key = intern::validated_serializable_string<validators::throw_when_field_key_invalid,escapers::escape_field_key>;
    using field_string_value = intern::validated_serializable_string<validators::throw_when_field_string_value_invalid,escapers::escape_field_string_value>;
    using measurement = intern::validated_serializable_string<validators::throw_when_measurement_invalid,escapers::escape_measurement>;

}

#endif //INFLUXDBLPTOOL_VALIDATED_SERIALIZABLE_STRING_H
