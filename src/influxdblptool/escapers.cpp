#include "influxdblptool/escapers.h"

namespace influxdblptool::escapers {

    template <char... Ch>
    std::string escape(std::string_view input) {
        std::stringstream ss;
        std::for_each(begin(input), end(input), [&ss](const char& inputChar){
            auto needsEscape = [](const char& matchChar) {
                return (...||(Ch==matchChar));
            };
            if (needsEscape(inputChar)) {
                ss << '\\';
            }
            ss << inputChar;
        });
        return ss.str();
    }

    std::string escape_measurement(std::string_view s) {
        return escape<',', ' '>(s);
    }

    std::string escape_tag_key(std::string_view s) {
        return escape<',', '=', ' '>(s);
    }

    std::string escape_tag_value(std::string_view s) {
        return escape<',', '=', ' '>(s);
    }

    std::string escape_field_key(std::string_view s) {
        return escape<',', '=', ' '>(s);
    }

    std::string escape_field_string_value(std::string_view s) {
        return escape<'\"', '\\'>(s);
    }

}