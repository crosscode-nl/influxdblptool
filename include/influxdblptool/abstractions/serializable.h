#ifndef INFLUXDBLPTOOL_SERIALIZABLE_H
#define INFLUXDBLPTOOL_SERIALIZABLE_H
#include <ostream>

namespace influxdblptool::abstractions {

    struct ISerializable {
        virtual void serialize(std::ostream &s) const = 0;

        virtual ~ISerializable() = default;
    };

    std::ostream &operator<<(std::ostream &os, const ISerializable &serializable);

}

#endif //INFLUXDBLPTOOL_SERIALIZABLE_H
