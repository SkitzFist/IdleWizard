#ifndef IDLE_MINER_COMPONENT_TYPE_H
#define IDLE_MINER_COMPONENT_TYPE_H

// debug
#include <string>

enum ComponentType {
    POSITION,
    SIZE,
    VELOCITY,
    TOTAL_COMPONENTS
};

inline std::string toString(ComponentType type) {
    switch (type) {
    case POSITION:
        return "Position";
        break;
    case SIZE:
        return "Size";
        break;
    case VELOCITY:
        return "Velocity";
        break;
    default:
        return "DEFAULT";
    }
}

#endif
