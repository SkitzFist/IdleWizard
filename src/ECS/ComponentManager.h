#ifndef IDLE_MINER_COMPONENT_MANAGER_H
#define IDLE_MINER_COMPONENT_MANAGER_H

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Component.h"
#include "ComponentType.h"

/*
    Note: If ever too slow, try switch unordered_set to a bitset instead
*/

struct ComponentManager {
    ComponentManager();
    // entity
    void createEntity();
    void addComponentToEntity(int entityId, ComponentType componentType);
    void removeComponentFromEntity(int entityId, ComponentType componentType);
    void removeEntity(int entityId);
    bool hasComponent(int entityId, ComponentType componentType) const;
    std::vector<std::unordered_set<ComponentType>> entityToComponentLookup;

    // Component
    void registerComponent(const ComponentType type, const size_t dataTypeSize, const int initCapacity = 100);
    std::unordered_map<ComponentType, Component> components;
};

#endif
