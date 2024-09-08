#ifndef TESTS_SPATIAL_TEST_HPP
#define TESTS_SPATIAL_TEST_HPP

#include "TileIndexStructure.h"
#include "TileStructure.h"

#include "Timer.h"

#include "raylib.h"

inline void spatialTest(){
  const int rows = 1;
  const int columns = 100;
  const int tileWidth = 10;
  const int tileHeight = 10;
  const float entitySize = 1.f;
  const int nrOfEntities = 100000;

  TileIndexStructure tis(tileWidth, tileHeight, rows, columns);
  TileStructure ts(tileWidth, tileHeight, rows, columns);

  Timer t;

  /////////////////////////
  ///  FILL TEST      ////
  ///////////////////////

  //tileStructure
  t.begin();
  for(int i = 0; i < nrOfEntities; ++i){
    float x = GetRandomValue(0, tileWidth * columns);
    float y = GetRandomValue(0, tileHeight * rows);
    ts.addEntity(i, x, y, entitySize, entitySize);
  }
  std::cout << "Filling, tileStructure: " << t.getDuration() << "ms\n";

  t.begin();
  for (int i = 0; i < nrOfEntities; ++i) {
    float x = GetRandomValue(0, tileWidth * columns);
    float y = GetRandomValue(0, tileHeight * rows);
    add(tis, i, x, y, entitySize, entitySize);
  }
  sortAllElementsByWorldIndex(tis);
  std::cout << "Filling, tileIndexStructure: " << t.getDuration() << "ms\n";
}

#endif
