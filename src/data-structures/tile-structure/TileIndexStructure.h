#ifndef IDLE_MINER_TILE_INDEX_STRUCTURE_H
#define IDLE_MINER_TILE_INDEX_STRUCTURE_H

#include <vector>
#include <unordered_set>
#include <algorithm>
#include <numeric>

//debug
#include <iostream>

struct TileIndexStructure{
  std::vector<int> id;
  std::vector<int> worldIndex;
  const int tileWidth;
  const int tileHeight;
  const int rows, columns;

  TileIndexStructure(const int tileWidth, const int tileHeight, const int rows, const int columns) : 
                                                                                                    tileWidth(tileWidth), 
                                                                                                    tileHeight(tileHeight),
                                                                                                    rows(rows),
                                                                                                    columns(columns){
    int toReserve = 100000;
    id.reserve(toReserve);
    worldIndex.reserve(toReserve);
  }
};

inline void clear(TileIndexStructure& structure){
  structure.id.clear();
  structure.worldIndex.clear();
}

inline void sortElementByWorldIndex(TileIndexStructure& structure, const int id, const int worldIndex, size_t vecIndex){

  size_t prevIndex = vecIndex - 1;

  while (prevIndex > 0 && structure.worldIndex[prevIndex] > worldIndex)
  {
    std::swap(structure.id[prevIndex], structure.id[vecIndex]);
    std::swap(structure.worldIndex[prevIndex], structure.worldIndex[vecIndex]);
    --vecIndex;
    --prevIndex;
  }
  
}

inline void sortAllElementsByWorldIndex(TileIndexStructure &structure) {
  // Sort both id and worldIndex in tandem using the worldIndex for comparison
  std::vector<size_t> indices(structure.id.size());
  std::iota(indices.begin(), indices.end(), 0);

  std::sort(indices.begin(), indices.end(), [&structure](size_t i1, size_t i2) {
      return structure.worldIndex[i1] < structure.worldIndex[i2];
  });

  // Apply the sorted order to the id and worldIndex vectors
  std::vector<int> sortedIds(structure.id.size());
  std::vector<int> sortedWorldIndices(structure.worldIndex.size());

  for (size_t i = 0; i < indices.size(); ++i) {
    sortedIds[i] = structure.id[indices[i]];
    sortedWorldIndices[i] = structure.worldIndex[indices[i]];
  }

  structure.id = std::move(sortedIds);
  structure.worldIndex = std::move(sortedWorldIndices);
}

inline void add(TileIndexStructure& structure, const int id, const float x, const float y, const float width, const float height){
  int gridX = static_cast<int>(x / structure.tileWidth);
  int gridY = static_cast<int>(y / structure.tileHeight);

  int worldIndex = gridY * structure.columns + gridX;

  size_t vecIndex = structure.id.size();
  structure.id.emplace_back(id);
  structure.worldIndex.emplace_back(worldIndex);
}

inline int getStartIndexOfWorldIndex(const TileIndexStructure& structure, const int worldIndex){
  for(size_t index = 0; index < structure.worldIndex.size(); ++index){
    if(structure.worldIndex[index] == worldIndex){
      return index;
    }
  }

  return -1;
}

inline void search(const TileIndexStructure& structure, 
                   std::unordered_set<int>& out, 
                   const float x, 
                   const float y, 
                   const float width, 
                   const float height){

  int gridX = x / structure.tileWidth;
  int gridY = y / structure.tileHeight;
  int worldIndex = y * structure.rows + gridX;

  int index = getStartIndexOfWorldIndex(structure, worldIndex);
  if(index == -1){
    return;
  }

  while (structure.worldIndex[index] == worldIndex) {
    out.emplace(structure.id[index]);
    ++index;
  }
  
}

inline void print(const TileIndexStructure& t){
  std::cout << "size: id " << t.id.size() << "  wIndex " << t.worldIndex.size() << '\n';
  for(size_t i = 0; i < t.id.size(); ++i){
    std::cout << "\t[" << i << "]: id: " << t.id[i] << "   worldIndex: " << t.worldIndex[i] << '\n';
  }
}

#endif
