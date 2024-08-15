#include "ComponentManager.h"

void ComponentManager::createEntity() {
    m_componentLookup.emplace_back();
}

void ComponentManager::addComponent(int entityId, ComponentType componentType) {
    m_componentLookup[entityId][componentType] = true;
}

void ComponentManager::removeComponent(int entityId, ComponentType componentType) {
    m_componentLookup[entityId][componentType] = false;
}

bool ComponentManager::hasComponent(int entityId, ComponentType componentType) const {
    return m_componentLookup[entityId][componentType];
}
