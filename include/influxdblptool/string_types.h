#ifndef INFLUXDBLPTOOL_VALIDATED_SERIALIZABLE_STRING_H
#define INFLUXDBLPTOOL_VALIDATED_SERIALIZABLE_STRING_H
#include <string>
#include "influxdblptool/validators.h"
#include "influxdblptool/escapers.h"

namespace influxdblptool {
    namespace intern {

        template <auto throw_when_invalid>
        class validated_string {
            std::string value_;
        public:
            explicit validated_string(std::string_view input) : value_{input} {
                throw_when_invalid(value_);
            }

            explicit validated_string(const char *input) : value_{input} {
                throw_when_invalid(value_);
            }

            explicit validated_string(std::string input) : value_{std::move(input)} {
                throw_when_invalid(value_);
            }

            validated_string(const validated_string<throw_when_invalid>& input) : value_{input.value_} {
                throw_when_invalid(value_);
            }

            validated_string(validated_string<throw_when_invalid>&& input) : value_{
                std::move(input.value_)} {
                throw_when_invalid(value_);
            }

            validated_string<throw_when_invalid>& operator=(std::string s) {
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

            const std::string& operator*() const {
                return value_;
            }

            bool operator<(const validated_string<throw_when_invalid>& rhs) const {
                return value_<rhs.value_;
            }

            bool operator>(const validated_string<throw_when_invalid>& rhs) const {
                return value_>rhs.value_;
            }

            bool operator==(const validated_string<throw_when_invalid>& rhs) const {
                return value_==rhs.value_;
            }

            bool operator!=(const validated_string<throw_when_invalid>& rhs) const {
                return value_!=rhs.value_;
            }
            validated_string<throw_when_invalid>& operator=(validated_string<throw_when_invalid> rhs) {
                value_ = std::move(rhs.value_);
                return *this;
            }
        };
    }

    using tag_key = intern::validated_string<validators::throw_when_tag_key_invalid>;
    using tag_value = intern::validated_string<validators::throw_when_tag_value_invalid>;
    using field_key = intern::validated_string<validators::throw_when_field_key_invalid>;
    using field_string_value = intern::validated_string<validators::throw_when_field_string_value_invalid>;
    using measurement_value = intern::validated_string<validators::throw_when_measurement_invalid>;

}

#endif //INFLUXDBLPTOOL_VALIDATED_SERIALIZABLE_STRING_H
