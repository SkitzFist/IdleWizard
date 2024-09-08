#include "ComponentManager.h"

////////////////////////////////////////////////////
///                ENTITIES                     ///
//////////////////////////////////////////////////

void ComponentManager::createEntity() {
    componentLookup.emplace_back();
}

void ComponentManager::addComponent(int entityId, ComponentType componentType) {
    componentLookup[entityId].emplace(componentType);
}

void ComponentManager::removeComponent(int entityId, ComponentType componentType) {
    componentLookup[entityId].erase(componentType);
}

void ComponentManager::removeEntity(int entityId) {
    std::swap(componentLookup[entityId], componentLookup.back());
    componentLookup.pop_back();
}

bool ComponentManager::hasComponent(int entityId, ComponentType componentType) const {
    return componentLookup[entityId].find(componentType) != componentLookup[entityId].end();
}

////////////////////////////////////////////////////
///                COMPONENTS                   ///
//////////////////////////////////////////////////

void ComponentManager::registerVectorComponent(ComponentType type, Component *component) {
    vectorComponentLookup[type] = component;
}