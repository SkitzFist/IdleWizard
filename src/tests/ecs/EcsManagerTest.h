#ifndef TESTS_ECS_MANAGER_H
#define TESTS_ECS_MANAGER_H

#include <iostream>

#include "Component.h"
#include "Components.h"
#include "EcsManager.h"
#include "ComponentType.h"
#include "EntityType.h"

inline bool componentsRefTest(){
  EcsManager ecs;
  Components& components = ecs.components;

  int num = 10;
  components.registerComponent(ComponentType::POSITION, sizeof(int), num);

  for(int i = 0; i < num; ++i){
    components[ComponentType::POSITION].add(&i, i);
  }

  for (int i = 0; i < num; ++i) {
    if(components[ComponentType::POSITION].get<int>(i) != ecs.components[ComponentType::POSITION].get<int>(i)){
      std::cout << "\tComponentsRef does not match ecs component\n";
      return false;
    }
  }

  return true;
}

inline bool validateIdDoesNotExist(Components& components, const int id){
  for(auto& pair : components.components){
    if(pair.second.getIndex(id) != -1){
      return false;
    }
  }

  return true;
}

inline bool removeTestSingleEntitySingleComponent(){
  EcsManager ecs;
  Components& components = ecs.components;
  constexpr const int num = 11;
  components.registerComponent(ComponentType::POSITION, sizeof(int), num);

  for (int i = 0; i < num; ++i) {
    ecs.createEntity(EntityType::BLOB);
    ecs.addComponent(i, ComponentType::POSITION);
    components[ComponentType::POSITION].add(&i, i);
  }

  constexpr const int numRemoves = 3;
  int removes[numRemoves] = {0, 3, 6};

  for(int i = 0; i < numRemoves; ++i){
    ecs.removeEntity(removes[i]);
  }

  constexpr const int expectedSize = num - numRemoves;
  if(ecs.entityTypes.size() != expectedSize){
    std::cout << "\tEntityTypes does not match expected size: " << ecs.entityTypes.size() << " != " << expectedSize << "\n";
    return false;
  }
  //std::cout << "\tEntitypes has expected size\n";

  if (ecs.entityToComponents.size() != expectedSize) {
    std::cout << "\tEntityToComponents does not match expected size: " << ecs.entityToComponents.size() << " != " << expectedSize << "\n";
    return false;
  }
  //std::cout << "\tEntitypes has expected size\n";

  for(int i = 0; i < numRemoves; ++i){
    if(!validateIdDoesNotExist(ecs.components, removes[i])){
      std::cout << "\tId Still exists\n";
      return false;
    }
  }
  //std::cout << "\tId does not exist\n";

  int expectedData[expectedSize] = {1, 2, 4, 5, 7, 8, 9, 10};
  int expectedIds[expectedSize] = {1, 2, 4, 5, 7, 8, 9, 10};

  for(int i = 0; i < expectedSize; ++i){
    if(components[ComponentType::POSITION].get<int>(expectedIds[i]) != expectedData[i]){
      std::cout << "\tExpected data does not match: " << components[ComponentType::POSITION].get<int>(i) << " != " << expectedData[i] << '\n';
      return false;
    }
  }
  //std::cout << "\tExpected data matches\n";

  return true;
}

inline bool componentTypeTest(){
  constexpr const int num = 10;
  EcsManager ecs;
  for(int i = 0; i < num; ++i){
    ecs.createEntity(EntityType::BLOB);
    ecs.addComponent(i, ComponentType::POSITION);
  }

  for(int i = 0; i < num; ++i){
    if(!ecs.hasComponent(i, ComponentType::POSITION)){
      std::cout << "\tComponentType was not added correctly\n";
      return false;
    }
  }

  for (int i = 0; i < num; ++i) {
    ecs.removeComponent(i, ComponentType::POSITION);
  }

  for (int i = 0; i < num; ++i) {
    if (ecs.hasComponent(i, ComponentType::POSITION)) {
      std::cout << "\tComponentType was not removed correctly\n";
      return false;
    }
  }

  return true;
}

inline bool ecsTests(){
  bool result = componentsRefTest();
  bool rv = !result ? result : true;
  std::cout << "ComponentsRefTest: " << result << "\n";

  result = removeTestSingleEntitySingleComponent();
  rv = !result ? result : true;
  std::cout << "ComponentsRemove: " << result << "\n";

  result = componentTypeTest();
  rv = !result ? result : true;
  std::cout << "ComponentType: " << result << "\n";

  return rv;
}

#endif
