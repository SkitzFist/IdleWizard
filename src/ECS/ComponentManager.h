#ifndef IDLE_MINER_COMPONENT_MANAGER_H
#define IDLE_MINER_COMPONENT_MANAGER_H

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Component.h"
#include "ComponentType.h"

struct ComponentManager {
    // entity
    void createEntity();
    void addComponent(int entityId, ComponentType componentType);
    void removeComponent(int entityId, ComponentType componentType);
    void removeEntity(int entityId);
    bool hasComponent(int entityId, ComponentType componentType) const;
    std::vector<std::unordered_set<ComponentType>> componentLookup;

    // Component
    void registerVectorComponent(ComponentType type, Component *component);
    std::unordered_map<ComponentType, Component *> vectorComponentLookup;
};

#endif
