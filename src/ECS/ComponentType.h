#ifndef IDLE_WIZARD_COMPONENT_TYPE_H
#define IDLE_WIZARD_COMPONENT_TYPE_H

#include <bitset>

enum ComponentType {
    POSITION,
    SIZE,
    TRANSFORM,
    COUNT
};

using ComponentSignature = std::bitset<ComponentType::COUNT>;

#endif
