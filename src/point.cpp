#include "influxdblptool/point.h"

namespace influxdblptool::intern {


    std::chrono::system_clock::time_point now()
    {
        return std::chrono::system_clock::now();
    }

}