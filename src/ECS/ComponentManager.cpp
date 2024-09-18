#include "ComponentManager.h"

//debug
#include <iostream>

ComponentManager::ComponentManager() {
}

////////////////////////////////////////////////////
///                ENTITIES                     ///
//////////////////////////////////////////////////

void ComponentManager::createEntity() {
    entityToComponentLookup.emplace_back();
}

void ComponentManager::addComponentToEntity(int entityId, ComponentType componentType) {
    entityToComponentLookup[entityId].emplace(componentType);
}

void ComponentManager::removeComponentFromEntity(int entityId, ComponentType componentType) {
    entityToComponentLookup[entityId].erase(componentType);
}

void ComponentManager::removeEntity(int entityId) {
    std::swap(entityToComponentLookup[entityId], entityToComponentLookup.back());
    entityToComponentLookup.pop_back();
}

bool ComponentManager::hasComponent(int entityId, ComponentType componentType) const {
    return entityToComponentLookup[entityId].find(componentType) != entityToComponentLookup[entityId].end();
}

////////////////////////////////////////////////////
///                COMPONENTS                   ///
//////////////////////////////////////////////////

void ComponentManager::registerComponent(const ComponentType type, const size_t dataTypeSize, const int initCapacity) {
    if((int) type != components.size()){
        std::cerr << "Components added in wrong order\n";
    }
    components.emplace(type, Component(dataTypeSize, initCapacity));
}