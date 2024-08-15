#ifndef IDLE_MINER_COMPONENT_MANAGER_H
#define IDLE_MINER_COMPONENT_MANAGER_H

#include <bitset>
#include <vector>

#include "ComponentType.h"

struct ComponentManager {
    void createEntity();
    void addComponent(int entityId, ComponentType componentType);
    void removeComponent(int entityId, ComponentType componentType);
    bool hasComponent(int entityId, ComponentType componentType) const;

    std::vector<std::bitset<TOTAL_COMPONENTS>> m_componentLookup;
};

#endif
