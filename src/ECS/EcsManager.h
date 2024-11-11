#ifndef IDLE_WIZARD_ENTITY_MANAGER_H
#define IDLE_WIZARD_ENTITY_MANAGER_H

#include <array>
#include <unordered_set>
#include <vector>

#include "ComponentType.h"
#include "Components.h"
#include "EntityType.h"
#include "EntityTypeMap.h"
#include "Systems.h"

class EcsManager {
  public:
    EcsManager();

    int createEntity(const EntityType type);
    void removeEntity(const int entityId);

    int copyEntity(const int entityId);

    // components
    bool hasComponent(const int index, const ComponentType type) const;
    void addComponent(const int index, const ComponentType type, void* data);
    void removeComponent(const int index, const ComponentType type);

    std::vector<EntityType> entityTypes;
    EntityTypeMap entityTypeMap;
    std::vector<ComponentSignature> entityToComponents;
    Components components;

    // systems
    Systems systems;

    // general
    int size;
};

#endif
