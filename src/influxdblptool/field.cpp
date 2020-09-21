#include "influxdblptool/field.h"

namespace influxdblptool {

    field_double::field_double() {}

    field_double::field_double(double value) : value_(value) {
        validators::throw_when_double_value_invalid(value_);
    }

    field_double::field_double(float value) : value_(value) {
        validators::throw_when_double_value_invalid(value_);
    }

    field_double::field_double(const field_double &s) : value_(s.value_) {
        validators::throw_when_double_value_invalid(value_);
    }

    field_double::operator double() const {
        return value_;
    }

    field_double &field_double::operator=(double value) {
        validators::throw_when_double_value_invalid(value_);
        value_ = value;
        return *this;
    }

    class field_variant_visitor {
        std::ostream *os_;
        public:
        explicit field_variant_visitor(std::ostream* os) : os_(os) {}
        void operator()(const field_double &v) {
            *os_ << std::to_string((double)v);
        }
        void operator()(const field_string_value &v) {
            *os_ << "\"" << v << "\"";

        }
        void operator()(const bool &v) {
            *os_ << (v?"t":"f");
        }
        void operator()(const uint64_t &v) {
            *os_ << std::to_string(v);
        }
        void operator()(const int64_t &v) {
            *os_ << std::to_string(v);
        }
    };

    void field::serialize(std::ostream &s) const {
        std::visit(field_variant_visitor{&s},*dynamic_cast<const field_variant*>(this));
    }

}