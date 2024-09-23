#ifndef TEST_COMPONENT_H
#define TEST_COMPONENT_H

#include <iostream>

#include "Component.h"

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

inline bool ComponentTest(){
  bool result = resizeTest();

  if(!result){
    return false;
  }

  return true;
}

#endif
