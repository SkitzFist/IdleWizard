#include "EntityManager.h"
#include "ComponentManager.h"
#include "VectorComponent.h"

// debug
#include <iostream>

EntityManager::EntityManager() : lastId(0) {
}

int EntityManager::createEntity(EntityType entityType) {
    entities.emplace_back(entityType);
    return (int)entities.size() - 1;
}

void EntityManager::destroyEntity(const int id, ComponentManager &componentManager) {
    const int lastId = (int)entities.size() - 1;
    EntityType entityTypeA = entities[id];
    EntityType entityTypeB = entities[lastId];

    if (entityTypeA != entityTypeB) {
        std::swap(entities[id], entities[lastId]);
    }

    entities.pop_back();

    // TODO this belongs more to the componentManager, but I'll leave it here for now.
    std::unordered_set<ComponentType> allComponents;
    allComponents.insert(componentManager.componentLookup[id].begin(), componentManager.componentLookup[id].end());
    allComponents.insert(componentManager.componentLookup[lastId].begin(), componentManager.componentLookup[lastId].end());

    for (const ComponentType component : allComponents) {
        bool aHasComponent = componentManager.hasComponent(id, component);
        bool bHasComponent = componentManager.hasComponent(lastId, component);

        if (aHasComponent && bHasComponent) {
            componentManager.vectorComponentLookup[component]->SwapDataThenPop(id);

        } else if (aHasComponent && !bHasComponent) {
            componentManager.vectorComponentLookup[component]->swapDataAndIdThenPop(id);

        } else if (!aHasComponent && bHasComponent) {
            componentManager.vectorComponentLookup[component]->switchId(lastId, id);
        }
    }
    // TODO remove from spatial (could maybe do that as a first step, before this method call, instead)
    componentManager.removeEntity(id);
}

std::size_t EntityManager::getNumEntities() const {
    return entities.size();
}

void EntityManager::clear() {
    entities.clear();
}

void EntityManager::print() {
    std::cout << "\nEntity Manager:\n";
    for (size_t i = 0; i < entities.size(); ++i) {
        std::cout << "[" << i << "]: " << toString(entities[i]) << '\n';
    }
}
