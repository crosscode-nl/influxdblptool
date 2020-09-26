#include "influxdblptool/point.h"

namespace influxdblptool {

    namespace time {

        std::chrono::system_clock::time_point now()
        {
            return std::chrono::system_clock::now();
        }

    }

    insert_prefix::operator std::string() const {
        return "INSERT ";
    }

}