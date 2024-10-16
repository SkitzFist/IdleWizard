#include "EcsManager.h"

#include <bitset>

EcsManager::EcsManager() : size(0) {
}

int EcsManager::createEntity(const EntityType type) {
    entityTypes.emplace_back(type);
    entityToComponents.emplace_back();
    entityTypeMap.add(type, size);
    return size++;
}

void EcsManager::removeEntity(const int entityId) {

    if (entityId >= size || entityId < 0) {
        return;
    }

    /*
      1. remove entityType & typeMap [X]
      2. loop through all components [X]
        2.1 swap data pop back <-- A and B has component [X]
        2.2 swap data & id pop back and sort element <-- only A has component [X]
        2.3 swithch id and sort element <-- only B has component [X]
      3. remove from entityToComponents [X]
    */

    // 1. remove entityType & update typeMap [X]
    const int aIndex = entityId;
    const int bIndex = size - 1;
    EntityType a = entityTypes[aIndex];
    EntityType b = entityTypes[bIndex];

    if (a == b) {
        entityTypeMap.remove(a, bIndex);
    } else {
        std::swap(entityTypes[entityId], entityTypes[bIndex]);
        entityTypeMap.switchId(b, bIndex, aIndex);
        entityTypeMap.remove(a, aIndex);
    }

    entityTypes.pop_back();

    // 2. loop through all components[X]
    ComponentSignature aOrBComponentTypes = entityToComponents[aIndex] | entityToComponents[bIndex];

    // TODO: _Find_first and _Find_next is GCC and will not work with emscripten
    for (size_t i = aOrBComponentTypes._Find_first(); i < aOrBComponentTypes.size(); i = aOrBComponentTypes._Find_next(i)) {

        ComponentType type = (ComponentType)i;
        bool aHasComponent = hasComponent(aIndex, type);
        bool bHasComponent = hasComponent(bIndex, type);
        Component &component = components[i];

        if (aHasComponent && bHasComponent) {
            // 2.1 swap data pop back <-- A and B has component[X]
            components[i].swapDataPopBack(aIndex);

        } else if (aHasComponent && !bHasComponent) {
            // 2.2 swap data & id pop back and sort element <-- only A has component [X]
            components[i].swapDataAndIdPopBack(aIndex);

        } else if (!aHasComponent && bHasComponent) {
            // 2.3 swithch id and sort element <-- only B has component [X]
            components[i].switchId(bIndex, aIndex);
        }
    }

    // 3. remove from entityToComponents [X]
    std::swap(entityToComponents[aIndex], entityToComponents[bIndex]);
    entityToComponents.pop_back();

    --size;
}

bool EcsManager::hasComponent(const int index, const ComponentType type) const {
    return entityToComponents[index].test(type);
}

void EcsManager::addComponent(const int index, const ComponentType type, void *data) {
    components[type].add(data, index);
    entityToComponents[index].set(type);
}

void EcsManager::removeComponent(const int index, const ComponentType type) {
    entityToComponents[index].reset(type);
    components[type].swapDataAndIdPopBack(index);
}
