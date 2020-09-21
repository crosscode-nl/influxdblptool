#ifndef INFLUXDBLPTOOL_SERIALIZABLE_H
#define INFLUXDBLPTOOL_SERIALIZABLE_H
#include <ostream>

namespace influxdblptool::abstractions {

    struct serializable {
        virtual void serialize(std::ostream &s) const = 0;

        virtual ~serializable() = default;
    };

    std::ostream &operator<<(std::ostream &os, const serializable &serializable);

}

#endif //INFLUXDBLPTOOL_SERIALIZABLE_H
