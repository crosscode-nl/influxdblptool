#ifndef INFLUXDBLPTOOL_IESCAPE_H
#define INFLUXDBLPTOOL_IESCAPE_H
#include <string>

namespace influxdblptool {

    struct IEscape {
        virtual std::string escape(std::string_view s) const = 0;
        virtual ~IEscape() = default;
    };

}

#endif //INFLUXDBLPTOOL_IESCAPE_H
