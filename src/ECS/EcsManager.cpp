#include "EcsManager.h"

EcsManager::EcsManager() : size(0){

}

int EcsManager::createEntity(const EntityType type){
  entityTypes.emplace_back(type);
  entityToComponents.emplace_back();
  return size++;
}

void EcsManager::removeEntity(const int entityId){

  if(entityId >= entityTypes.size()){
    return;
  }

  /*
    1. remove entityType [X]
    2. loop through all components [X]
      2.1 swap data pop back <-- A and B has component [X]
      2.2 swap data & id pop back and sort element <-- only A has component [X]
      2.3 swithch id and sort element <-- only B has component [X]
    3. remove from entityToComponents [X]
    4. remove from spatial? []
  */

    //1. remove entityType [X]
    const int aIndex = entityId;
    const int bIndex = entityTypes.size() - 1;
    EntityType a = entityTypes[aIndex];
    EntityType b = entityTypes[bIndex];
    if(a != b){
      std::swap(entityTypes[entityId], entityTypes[bIndex]);
    }
    entityTypes.pop_back();


    //2. loop through all components[X]
    std::unordered_set<ComponentType> aAndBComponentTypes;
    aAndBComponentTypes.insert(entityToComponents[aIndex].begin(), entityToComponents[aIndex].end());
    aAndBComponentTypes.insert(entityToComponents[bIndex].begin(), entityToComponents[bIndex].end());

    for(const ComponentType componentType : aAndBComponentTypes){
      bool aHasComponent = hasComponent(aIndex, componentType);
      bool bHasComponent = hasComponent(bIndex, componentType);

      if(aHasComponent && bHasComponent){
          //2.1 swap data pop back <-- A and B has component[X]
          components[componentType].swapDataPopBack(aIndex);
      } else if(aHasComponent && !bHasComponent){
          // 2.2 swap data & id pop back and sort element <-- only A has component [X]
          components[componentType].swapDataAndIdPopBack(aIndex);
      } else if (!aHasComponent && bHasComponent){
          // 2.3 swithch id and sort element <-- only B has component [X]
          components[componentType].switchId(aIndex, bIndex);
      }
    }

    //3. remove from entityToComponents [X]
    std::swap(entityToComponents[aIndex], entityToComponents[bIndex]);
    entityToComponents.pop_back();

    --size;
}

bool EcsManager::hasComponent(const int index, const ComponentType type) const {
  return entityToComponents[index].find(type) != entityToComponents[index].end();
}

void EcsManager::addComponent(const int index, const ComponentType type) {
  entityToComponents[index].emplace(type);
}

void EcsManager::removeComponent(const int index, const ComponentType type){
  entityToComponents[index].erase(type);
  components[type].swapDataAndIdPopBack(index);
}
