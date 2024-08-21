#ifndef IDLE_MINER_ENTITY_MANAGER_H
#define IDLE_MINER_ENTITY_MANAGER_H

#include <vector>

#include "EntityType.h"

struct ComponentManager;

struct EntityManager {
    EntityManager();
    int createEntity(EntityType entityType);
    bool destroyEntity(const int id, ComponentManager &componentManager);

    std::size_t getNumEntities() const;
    void clear();

    // member variables
    int lastId;
    std::vector<EntityType> entities;
};

#endif
