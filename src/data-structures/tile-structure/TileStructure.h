#ifndef IDLE_WIZARD_TILE_STRUCTURE_H
#define IDLE_WIZARD_TILE_STRUCTURE_H

#include <algorithm>
#include <execution>
#include <numeric>
#include <unordered_set>
#include <vector>

//debug
#include <iostream>


/*
  Todo, could store the start index and size of for world index.
  for example World index 0 contains 1000 entities and starts at index 25
*/

struct TileStructure{
  std::vector<int> id;
  std::vector<int> worldIndex;
  const int tileWidth;
  const int tileHeight;
  const int rows, columns;

  TileStructure(const int tileWidth, const int tileHeight, const int rows, const int columns) : 
                                                                                                    tileWidth(tileWidth), 
                                                                                                    tileHeight(tileHeight),
                                                                                                    rows(rows),
                                                                                                    columns(columns){
    int toReserve = 100000;
    id.reserve(toReserve);
    worldIndex.reserve(toReserve);
  }
};

inline void clear(TileStructure& structure){
  structure.id.clear();
  structure.worldIndex.clear();
}

inline void sortAllElementsByWorldIndex(TileStructure &structure) {
  std::vector<size_t> indices(structure.id.size());
  std::iota(indices.begin(), indices.end(), 0);

  std::sort(indices.begin(), indices.end(), [&structure](size_t i1, size_t i2) {
      return structure.worldIndex[i1] < structure.worldIndex[i2];
  });

  std::vector<int> sortedIds(structure.id.size());
  std::vector<int> sortedWorldIndices(structure.worldIndex.size());

  for (size_t i = 0; i < indices.size(); ++i) {
    sortedIds[i] = structure.id[indices[i]];
    sortedWorldIndices[i] = structure.worldIndex[indices[i]];
  }

  structure.id = std::move(sortedIds);
  structure.worldIndex = std::move(sortedWorldIndices);
}

inline void addToStructure(TileStructure& structure, const int id, const float x, const float y, const float width, const float height){
  int gridX = static_cast<int>(x / structure.tileWidth);
  int gridY = static_cast<int>(y / structure.tileHeight);

  int worldIndex = gridY * structure.columns + gridX;

  size_t vecIndex = structure.id.size();
  structure.id.emplace_back(id);
  structure.worldIndex.emplace_back(worldIndex);
}

inline int getStartIndexOfWorldIndex(const TileStructure &structure, const int worldIndex) {
  auto it = std::lower_bound(structure.worldIndex.begin(), structure.worldIndex.end(), worldIndex);
  if (it != structure.worldIndex.end() && *it == worldIndex) {
    return std::distance(structure.worldIndex.begin(), it);
  }
  return -1;
}

inline void search(const TileStructure &structure,
                   std::unordered_set<int> &out,
                   const float x,
                   const float y,
                   const float width,
                   const float height) {
  // Calculate the min and max grid coordinates
  const int minGridX = static_cast<int>(x / structure.tileWidth);
  const int minGridY = static_cast<int>(y / structure.tileHeight);
  const int maxGridX = static_cast<int>((x + width) / structure.tileWidth);
  const int maxGridY = static_cast<int>((y + height) / structure.tileHeight);

  // Loop through all grid cells that intersect the search range
  for (int gridY = minGridY; gridY <= maxGridY; ++gridY) {
    for (int gridX = minGridX; gridX <= maxGridX; ++gridX) {
        const int worldIndex = gridY * structure.columns + gridX;

        // Get the starting index for this world index
        int index = getStartIndexOfWorldIndex(structure, worldIndex);
        if (index == -1) {
            continue; // No entries for this worldIndex
        }

        // Gather all entities within this world index
        while (index < structure.worldIndex.size() && structure.worldIndex[index] == worldIndex) {
            out.emplace(structure.id[index]);
            ++index;
        }
    }
  }
}

inline void print(const TileStructure& t){
  std::cout << "size: id " << t.id.size() << "  wIndex " << t.worldIndex.size() << '\n';
  for(size_t i = 0; i < t.id.size(); ++i){
    std::cout << "\t[" << i << "]: id: " << t.id[i] << "   worldIndex: " << t.worldIndex[i] << '\n';
  }
}

#endif
