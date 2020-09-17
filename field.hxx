#ifndef INFLUXDBLPTOOL_FIELD_HXX
#define INFLUXDBLPTOOL_FIELD_HXX
#include <variant>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <string_view>
#include <algorithm>
#include <sstream>
#include <map>
#include <cmath>


struct EscapeQuotes : IEscape
{
    std::string escape(std::string_view s) const override {
        std::stringstream ss;
        ss << "\"";
        std::for_each(begin(s),end(s),[&ss](const auto &c){
            switch (c) {
                case '\"' : ss << "\\";
            }
            ss << c;
        });
        ss << "\"";
        return ss.str();
    }
};


template <typename TFloatType>
class valid_floating_point
{
    static_assert(std::is_floating_point<TFloatType>::value,"TFloatType must a a floating point type.");
    TFloatType value_;
    void validateValue() {
        if (std::isnan(value_)) throw std::invalid_argument("NaN value not allowed.");
        if (std::isinf(value_)) throw std::invalid_argument("Infinite value not allowed.");
    }
public:
    explicit valid_floating_point() {}
    explicit valid_floating_point(TFloatType value) : value_(value) {
        validateValue();
    }
    valid_floating_point(const valid_floating_point& s) : value_(s.value_) {
        validateValue();
    }

    explicit operator TFloatType() const {
        return value_;
    }

    valid_floating_point& operator=(TFloatType value) {
        value_ = value;
        validateValue();
        return *this;
    }

};

using ValidDouble = valid_floating_point<double>;
using ValidFloat = valid_floating_point<float>;

using FieldVariant = std::variant<std::string,bool,ValidDouble,ValidFloat,std::uint64_t,std::int64_t>;
//using FieldVariant = std::variant<std::string,bool>;


template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

template <typename TEscape>
class field : public FieldVariant, public ISerializable
{

    TEscape escaper_;
    public:
    using FieldVariant::variant;

    void serialize(std::ostream &s) const override {
        std::visit(overloaded{
             [](const std::string &v){

             },
             [](const bool &v){

             },
             [](const ValidDouble &v){

             },
             [](const ValidFloat &v){

             },
             [](const uint64_t &v){

             },
             [](const int64_t &v){

             }
        },*dynamic_cast<const FieldVariant*>(this));
    }
};

using Field = field<EscapeQuotes>;

class NotEmptyValidator { // There will be multiple validators and an aggregate validator
    public:
    void throwWhenInvalid(std::string_view sv) {
        if (sv.empty()) throw std::invalid_argument("Argument cannot be empty.");
    }
};

template<typename TValidator>
class validated_string {
    TValidator validator_;
    std::string value_;
public:
    explicit validated_string(std::string value) : value_(std::move(value)) {
        validator_.throwWhenInvalid(value_);
    }
    validated_string<TValidator>& operator=(std::string s) {
        validator_.throwWhenInvalid(s);
        value_ = std::move(s);
        return *this;
    }
};

template <typename TEscape, typename TValidator>
class key : public validated_string<TValidator>, public ISerializable {
private:
    TEscape escaper_;
public:
    void serialize(std::ostream &s) const override{
        s << escaper_.escape(*this);
    };
};

using Key = key<EscapeQuotes,NotEmptyValidator>;
/*
class MyType {
    double value_;
public:
    MyType() {

    }

    MyType(const MyType& s) : value_(s.value_) {
        if (std::isnan(value_)) throw std::invalid_argument("NaN value not allowed.");
        if (std::isinf(value_)) throw std::invalid_argument("Infinite value not allowed.");
    }

    explicit MyType(double v) : value_(v) {
        if (std::isnan(value_)) throw std::invalid_argument("NaN value not allowed.");
        if (std::isinf(value_)) throw std::invalid_argument("Infinite value not allowed.");
    }

    explicit operator double() const {
        return value_;
    }

    MyType& operator=(double value) {
        value_ = value;
        return *this;
    }

};

using TestVariant = std::variant<std::string,MyType,int>;
*/
int main() {
    FieldVariant v;
    Field f{true};
    std::visit([](auto o){},(FieldVariant)f);
}


#endif //INFLUXDBLPTOOL_FIELD_HXX
