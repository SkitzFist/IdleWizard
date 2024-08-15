#ifndef IDLE_MINER_ENTITY_MANAGER_H
#define IDLE_MINER_ENTITY_MANAGER_H

#include <vector>

#include "EntityType.h"

struct EntityManager {
    EntityManager();
    int createEntity(EntityType entityType);
    void destroyEntity(const int id);

    std::size_t getNumEntities() const;
    void clear();

    // member variables
    int lastId;
    std::vector<EntityType> entities;
};

#endif
