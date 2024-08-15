#include "EntityManager.h"

EntityManager::EntityManager() : lastId(0) {
}

int EntityManager::createEntity(EntityType entityType) {
    entities.emplace_back(entityType);
    return lastId++;
}

void EntityManager::destroyEntity(const int id) {
    /*
        Get id and type of the last entity.

        get position and remove last entity from quadtree

        check if same type

        if(==){
            popback from entity list
            swap data on components, pop back.
            get components -> swap data & pop back
        } else {
            swap in entityList
            get components -> components == swap data & pop back
                              components != remove id from component. swap data & id then pop back
        }

        swap data on same components, pop back
        remove from different components
    */
}

std::size_t EntityManager::getNumEntities() const {
    return entities.size();
}

void EntityManager::clear() {
    entities.clear();
}
