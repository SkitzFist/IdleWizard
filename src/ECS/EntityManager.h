#ifndef IDLE_MINER_ENTITY_MANAGER_H
#define IDLE_MINER_ENTITY_MANAGER_H

#include <vector>

#include "EntityType.h"

struct ComponentManager;

struct EntityManager {
    std::vector<EntityType> entities;

    EntityManager();
    void clear();
    int createEntity(EntityType entityType);
    bool destroyEntity(const int id, ComponentManager &componentManager);
};

#endif
