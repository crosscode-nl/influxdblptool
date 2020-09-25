#include "influxdblptool/escapers.h"
#include <numeric>

namespace influxdblptool::escapers {


    template <char... Ch>
    std::size_t escape_count(std::string_view input) {
        auto char_count = [](std::size_t& in, const char& inputChar) {
            auto needsEscape = [](const char& matchChar) {
                return (...||(Ch==matchChar));
            };
            return in + ((needsEscape(inputChar)?std::size_t{2}:std::size_t{1}));
        };

        return std::accumulate(begin(input), end(input),std::size_t{0},char_count);
    }

    template <char... Ch>
    std::string escape(std::string_view input) {
        std::string result;
        result.reserve(escape_count<Ch...>(input));
        auto escape_char = [&result](const char& inputChar){
            auto needsEscape = [](const char& matchChar) {
                return (...||(Ch==matchChar));
            };
            if (needsEscape(inputChar)) {
                result += '\\';
            }
            result += inputChar;
        };
        std::for_each(begin(input), end(input),escape_char);
        return result;
    }

    std::string escape_measurement(std::string_view s) {
        return escape<',', ' '>(s);
    }

    std::size_t escape_measurement_count(std::string_view s) {
        return escape_count<',', ' '>(s);
    }

    std::string escape_tag_key(std::string_view s) {
        return escape<',', '=', ' '>(s);
    }

    std::size_t escape_tag_key_count(std::string_view s) {
        return escape_count<',', '=', ' '>(s);
    }

    std::string escape_tag_value(std::string_view s) {
        return escape<',', '=', ' '>(s);
    }

    std::size_t escape_tag_value_count(std::string_view s) {
        return escape_count<',', '=', ' '>(s);
    }

    std::string escape_field_key(std::string_view s) {
        return escape<',', '=', ' '>(s);
    }

    std::size_t escape_field_key_count(std::string_view s) {
        return escape_count<',', '=', ' '>(s);
    }

    std::string escape_field_string_value(std::string_view s) {
        return escape<'\"', '\\'>(s);
    }

    std::size_t escape_field_string_value_count(std::string_view s) {
        return escape_count<'\"', '\\'>(s);
    }

}