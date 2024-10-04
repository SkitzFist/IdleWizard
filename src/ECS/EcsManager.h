#ifndef IDLE_WIZARD_ENTITY_MANAGER_H
#define IDLE_WIZARD_ENTITY_MANAGER_H

#include <unordered_set>
#include <vector>

#include "ComponentType.h"
#include "Components.h"
#include "EntityType.h"

class EcsManager{
public:
  EcsManager();

  int createEntity(const EntityType type);
  void removeEntity(const int entityId);

  bool hasComponent(const int index, const ComponentType type) const;
  void addComponent(const int index, const ComponentType type);
  void removeComponent(const int index, const ComponentType type);
  
  std::vector<EntityType> entityTypes;
  std::vector<std::unordered_set<ComponentType>> entityToComponents; //todo switch to bitsets
  Components components;
  int size;

  private:

};

#endif
