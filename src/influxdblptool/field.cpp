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
            *os_ << (double)v;
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

    field::field(const double &v) : field_variant{field_double{v}} {}
    field::field(const float &v) : field_variant{field_double{v}} {}
    field::field(const int32_t &v) : field_variant{int64_t{v}} {}
    field::field(const int16_t &v) : field_variant{int64_t{v}} {}
    field::field(const int8_t &v) : field_variant{int64_t{v}} {}
    field::field(const uint32_t &v) : field_variant{uint64_t{v}} {}
    field::field(const uint16_t &v) : field_variant{uint64_t{v}} {}
    field::field(const uint8_t &v) : field_variant{uint64_t{v}} {}
    field::field(const char* v) : field_variant{field_string_value{v}} {}
    field::field(std::string v) : field_variant{field_string_value{std::move(v)}} {}
    field::field(std::string_view v) : field_variant{field_string_value{v}} {}

    void field::serialize(std::ostream &s) const {
        std::visit(field_variant_visitor{&s},*dynamic_cast<const field_variant*>(this));
    }

}