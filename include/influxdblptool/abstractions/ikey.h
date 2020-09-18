#ifndef INFLUXDBLPTOOL_IKEY_H
#define INFLUXDBLPTOOL_IKEY_H
#include "iserializable.h"
#include "iescape.h"

namespace influxdblptool {

    template <typename TValidator, typename TEscaper>
    class IKey : public ISerializable {
        static_assert(std::is_base_of<IEscape,TEscaper>::value,"TEscaper must implement IEscape.");
        static_assert(std::is_base_of<IEscape,TEscaper>::value,"TValidator must implement IValidate.");
        TEscaper escaper_;
        TValidator validator_;
        std::string value_;
    public:
        IKey(std::string v) : value_(std::move(v)) {
            validator_.validate(v);
        }
        explicit operator std::string() const {
            return value_;
        }
        bool operator==(const IKey<TValidator,TEscaper> &rhs) {
            return value_==rhs.value_;
        }
        bool operator<(const IKey<TValidator,TEscaper> &rhs) {
            return value_<rhs.value_;
        }
        void serialize(std::ostream &s) const override {
            s << escaper_.escape(value_);
        }
    };

}

#endif //INFLUXDBLPTOOL_IKEY_H
