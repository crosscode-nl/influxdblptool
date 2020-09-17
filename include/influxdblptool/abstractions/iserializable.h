#ifndef INFLUXDBLPTOOL_ISERIALIZABLE_H
#define INFLUXDBLPTOOL_ISERIALIZABLE_H
#include <ostream>

namespace influxdblptool {

    struct ISerializable {
        virtual void serialize(std::ostream &s) const = 0;

        virtual ~ISerializable() = default;
    };

    std::ostream &operator<<(std::ostream &os, const ISerializable &serializable);

}

#endif //INFLUXDBLPTOOL_ISERIALIZABLE_H
