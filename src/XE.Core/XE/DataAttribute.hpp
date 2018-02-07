
#ifndef __XE_DATAATTRIBUTE_HPP__
#define __XE_DATAATTRIBUTE_HPP__

#include <XE/DataType.hpp>

namespace XE {
    struct DataAttribute {
        DataType Type;
        std::int16_t Dimension;
        std::int16_t Count;
        char Name[16];
    };
}

#endif
