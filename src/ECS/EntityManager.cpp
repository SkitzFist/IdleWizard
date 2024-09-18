#include "EntityManager.h"
#include "Component.h"
#include "ComponentManager.h"
#include "ComponentUtils.h"

// debug
#include "raylib.h"

EntityManager::EntityManager() {
}

int EntityManager::createEntity(EntityType entityType) {
    entities.emplace_back(entityType);
    return (int)entities.size() - 1;
}

bool EntityManager::destroyEntity(const int id, ComponentManager &componentManager) {
    if (entities.empty()) {
        return false;
    }

    const int lastId = (int)entities.size() - 1;
    EntityType entityTypeA = entities[id];
    EntityType entityTypeB = entities[lastId];

    if (entityTypeA != entityTypeB) {
        std::swap(entities[id], entities[lastId]);
    }

    // TODO this belongs more to the componentManager, but I'll leave it here for now.
    std::unordered_set<ComponentType> bothEntitiesComponents;
    bothEntitiesComponents.insert(componentManager.entityToComponentLookup[id].begin(), componentManager.entityToComponentLookup[id].end());
    bothEntitiesComponents.insert(componentManager.entityToComponentLookup[lastId].begin(), componentManager.entityToComponentLookup[lastId].end());

    for (const ComponentType component : bothEntitiesComponents) {
        bool aHasComponent = componentManager.hasComponent(id, component);
        bool bHasComponent = componentManager.hasComponent(lastId, component);
        Component& c = componentManager.components[component];
        bool success = true;

        if (aHasComponent && bHasComponent) {
            success = swapDataThenPopBack(c, id);
        } else if (aHasComponent && !bHasComponent) {
            success = swapDataAndIdThenPopBack(c, id);
        } else if (!aHasComponent && bHasComponent) {
            success = switchId(c, lastId, id);
        }

        if (!success) {
            TraceLog(LOG_ERROR, "EntityManager: Could not remove entity");
            return false;
        }
    }

    entities.pop_back();
    componentManager.removeEntity(id);

    return true;
}

void EntityManager::clear() {
    entities.clear();
}
