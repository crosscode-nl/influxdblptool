#ifndef INFLUXDBLPTOOL_ESCAPER_H
#define INFLUXDBLPTOOL_ESCAPER_H
#include "influxdblptool/abstractions/iescape.h"
#include <algorithm>
#include <sstream>
#include <array>

namespace influxdblptool {

    template <char... Ch>
    struct escaper : public IEscape {
        [[nodiscard]] std::string escape(std::string_view s) const override {
            std::stringstream ss;
            std::for_each(begin(s),end(s),[&ss,this](const char &c){
                auto compare = [&c](const char &b){
                    return c==b;
                };
                std::array<char,sizeof...(Ch)> escapeChars{Ch...};
                if (std::any_of(std::begin(escapeChars),std::end(escapeChars),compare)) {
                    ss << '\\';
                }
                ss << c;
            });
            return ss.str();
        }
    };

    using MeasurementEscaper = escaper<',',' '>;
    using TagKeyEscaper = escaper<',','=',' '>;
    using TagValueEscaper = escaper<',','=',' '>;
    using FieldKeyEscaper = escaper<',','=',' '>;
    using FieldValueEscaper = escaper<'\"','\\'>;
}

#endif //INFLUXDBLPTOOL_ESCAPER_H
