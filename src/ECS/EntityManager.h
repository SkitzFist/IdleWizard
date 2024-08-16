#ifndef IDLE_MINER_ENTITY_MANAGER_H
#define IDLE_MINER_ENTITY_MANAGER_H

#include <vector>

#include "EntityType.h"

// debug
#include <string>

struct ComponentManager;

inline std::string toString(EntityType type) {
    switch (type) {
    case EntityType::BLOB:
        return "blob";
        break;
    case EntityType::TREE:
        return "tree";
        break;
    default:
        return "";
        break;
    }
}

struct EntityManager {
    EntityManager();
    int createEntity(EntityType entityType);
    void destroyEntity(const int id, ComponentManager &componentManager);

    std::size_t getNumEntities() const;
    void clear();

    // member variables
    int lastId;
    std::vector<EntityType> entities;

    // debug
    void print();
};

#endif
