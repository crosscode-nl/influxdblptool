#include "influxdblptool/field_value.h"

namespace influxdblptool {

    field_double::field_double() {}

    field_double::field_double(double value) : value_(value) {
        validators::throw_when_double_value_invalid(value_);
    }

    field_double::field_double(float value) : value_(value) {
        validators::throw_when_double_value_invalid(value_);
    }

    field_double::field_double(const field_double& s) : value_(s.value_) {
        validators::throw_when_double_value_invalid(value_);
    }

    field_double::operator double() const {
        return value_;
    }

    field_double& field_double::operator=(double value) {
        validators::throw_when_double_value_invalid(value_);
        value_ = value;
        return *this;
    }

    field_double& field_double::operator=(const field_double& v) {
        value_ = v.value_;
        return *this;
    }

    class assigning_visitor {
        field_value *f_;
    public:
        explicit assigning_visitor(field_value* f) : f_(f) {}

        template <typename T>
        void operator()(const T& v) {
            *f_ = v;
        }
    };
    field_value::field_value() {}
    field_value::field_value(field_string_value v) : field_variant_{std::move(v)} {}
    field_value::field_value(field_double v) : field_variant_{std::move(v)} {}
    field_value::field_value(bool v) : field_variant_{v} {}
    field_value::field_value(const char* v) : field_variant_{field_string_value{v}} {}
    field_value::field_value(std::string_view v) : field_variant_{field_string_value{v}} {}
    field_value::field_value(std::string v) : field_variant_{field_string_value{std::move(v)}} {}

    field_value& field_value::operator=(bool v) {
        field_variant_ = v;
        return *this;
    }
    field_value& field_value::operator=(const field_string_value &v) {
        field_variant_ = v;
        return *this;
    }
    field_value& field_value::operator=(const field_double &v) {
        field_variant_ = v;
        return *this;
    }
    field_value& field_value::operator=(const char* v) {
        field_variant_ = field_string_value{v};
        return *this;
    }
    field_value& field_value::operator=(std::string v) {
        field_variant_ = field_string_value{std::move(v)};
        return *this;
    }

    field_value& field_value::operator=(std::string_view v) {
        field_variant_ = field_string_value{v};
        return *this;
    }

    field_value& field_value::operator=(const field_value& v) {
        assigning_visitor av{this};
        // We do it this quirky way, otherwise slicing warning is given by static analysis. We don't care about
        // slicing here.
        std::visit(av,v.field_variant_);
        return *this;
    }

    field_value::operator const field_variant&() const {
        return field_variant_;
    }

}