#ifndef IDLE_MINER_TILE_STRUCTURE_H
#define IDLE_MINER_TILE_STRUCTURE_H

#include <unordered_set>
#include <vector>

// debug
#include "raylib.h"

/*
  Note: In testing the structure hold 100k static entities in ~90 fps. The bottlneck is re-adding all the entities.
        If this ever becomes a problem try this solution:
          Batch clear. By clearing 1 / x of the structure at a time. Would also need to gather what entities has
          been cleared so they can be re-added. Clearing would have to take an unordered_set, startIndex and endIndex.
*/

class TileStructure {
  private:
    struct Tile {
        std::vector<int> entities;
    };

    struct IteratingProperties {
        int startIndex;
        int xLength;
        int yEndIndex;
    };

  public:
    TileStructure(const float tileWidth, const float tileHeight, const int rows, const int columns);

    float currentMaxWidth() const;
    float prevMaxWidth() const;
    float currentMaxHeight() const;
    float prevMaxHeight() const;

    void growColumns();
    // void growRows(); TODO

    void addEntity(const int entityId, const float x, const float y, float width, float height);
    void search(const float x, const float y, const float width, const float height, std::unordered_set<int> &out);

    void clear();

    // debug
    void debugRender() const;

  private:
    const float m_tileWidth;
    const float m_tileHeight;
    const int m_growthRate;
    const int m_rows;
    int m_columns;
    int m_totalNumberOfTiles;

    std::vector<Tile> m_tiles;

    IteratingProperties getIteratingProperties(const float x, const float y, const float width, const float height);

    // debug
    std::vector<Color> m_colors;
};

#endif
