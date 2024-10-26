#ifndef IDLE_WIZARD_COMPONENT_TYPE_H
#define IDLE_WIZARD_COMPONENT_TYPE_H

#include <bitset>

// debug
#include <string>

enum ComponentType {
    POSITION,
    SIZE,
    VELOCITY,
    COLOR,
    RESOURCE,
    COUNT
};

using ComponentSignature = std::bitset<ComponentType::COUNT>;

inline std::string toString(const ComponentType type) {
    switch (type) {
    case ComponentType::POSITION:
        return "Position";
    case ComponentType::SIZE:
        return "Size";
    case ComponentType::VELOCITY:
        return "Velocity";
    case ComponentType::COLOR:
        return "Color";
    case ComponentType::RESOURCE:
        return "Resource";
    case ComponentType::COUNT:
        return "COUNT";
    default:
        return "NO Component";
    }
}

#endif
