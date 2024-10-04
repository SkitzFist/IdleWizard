#ifndef IDLE_WIZARD_ENTITY_MANAGER_H
#define IDLE_WIZARD_ENTITY_MANAGER_H

#include <unordered_set>
#include <vector>

#include "ComponentType.h"
#include "Components.h"
#include "EntityType.h"
#include "Systems.h"

class EcsManager{
public:
  EcsManager();

  int createEntity(const EntityType type);
  void removeEntity(const int entityId);

  //components
  bool hasComponent(const int index, const ComponentType type) const;
  void addComponent(const int index, const ComponentType type);
  void removeComponent(const int index, const ComponentType type);
  
  std::vector<EntityType> entityTypes;
  std::vector<ComponentSignature> entityToComponents;
  Components components;
  int size;

  //systems
  Systems systems;
};

#endif
