#ifndef TEST_COMPONENT_H
#define TEST_COMPONENT_H

#include <iostream>

#include "Component.h"
#include "Components.h"

bool resizeTest(){
  Component c(sizeof(int), 10);

  //fill
  for(int i = 0; i < c.getCapacity(); ++i){
    c.add(&i);
  }
  
  try{
    c.resize(c.getCapacity() * 2);
  }catch(...){
    std::cout << "Component failed resizeTest\n";
    return false;
  }

  return true;
}

bool hugeCapTest(){
  int num = 10000000;
  
  try{
    Component c(sizeof(int), num);
    for (int i = 0; i < num; ++i) {
        c.add(&i);
    }
  } catch (...){
    std::cerr << "Component failed huge cap: " << num << '\n';
    return false;
  }

  return true;
}

bool hugeCapInComponentManager(){
  int num = 10000000;
  Components components;
  try {
    components.registerComponent(ComponentType::POSITION, sizeof(int), num);
    for (int i = 0; i < num; ++i) {
        components[ComponentType::POSITION].add(&i);
    }
  } catch (...) {
    std::cerr << "Component failed huge cap component manager: " << num << '\n';
    return false;
  }

  return true;
}

inline bool ComponentTest(){
  bool result = resizeTest();

  if(!result){
    return false;
  }

  result = hugeCapTest();
  if (!result) {
    return false;
  }

  result = hugeCapInComponentManager();
  if (!result) {
    return false;
  }

  return true;
}

#endif
