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

    field_double &field_double::operator=(const field_double &v) {
        value_ = v.value_;
        return *this;
    }

    class serializing_visitor {
        std::ostream *os_;
        public:
        explicit serializing_visitor(std::ostream* os) : os_(os) {}
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

    class assigning_visitor {
        field *f_;
    public:
        explicit assigning_visitor(field* f) : f_(f) {}

        template <typename T>
        void operator()(const T &v) {
            *f_ = v;
        }
    };

    field::field(const char* v) : field_variant{field_string_value{v}} {}
    field::field(std::string_view v) : field_variant{field_string_value{v}} {}
    field::field(std::string v) : field_variant{field_string_value{std::move(v)}} {}
    field& field::operator=(const char* v) {
        *(this) = field_string_value{v};
        return *this;
    }
    field& field::operator=(std::string v) {
        *(this) = field_string_value{std::move(v)};
        return *this;
    }

    field& field::operator=(std::string_view v) {
        *(this) = field_string_value{v};
        return *this;
    }

    field& field::operator=(const field &v) {
        assigning_visitor av{this};
        // We do it this quirky way, otherwise slicing warning is given by static analysis. We don't care about
        // slicing here.
        std::visit(av,*static_cast<const field_variant*>(&v));
        return *this;
    }

    void field::serialize(std::ostream& s) const {
        std::visit(serializing_visitor{&s},*dynamic_cast<const field_variant*>(this));
    }

}