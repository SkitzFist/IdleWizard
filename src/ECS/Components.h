#ifndef IDLE_WIZARD_COMPONENS_H
#define IDLE_WIZARD_COMPONENS_H

#include <unordered_map>

#include "ComponentType.h"
#include "Component.h"

struct Components {
    std::unordered_map<ComponentType, Component> components;

    void registerComponent(const ComponentType type, size_t dataTypeSize, size_t initCapacity) {
        components.try_emplace(type, Component(dataTypeSize, initCapacity));
    }

    Component &operator[](const ComponentType type) {
        auto it = components.find(type);
        if (it != components.end()) {
            return it->second;
        } else {
            throw std::runtime_error("Component not registered");
        }
    }

    const Component& operator[](const ComponentType type) const {
        auto it = components.find(type);
        if (it != components.end()) {
            return it->second;
        } else {
            throw std::runtime_error("Component not registered");
        }
    }
};

#endif