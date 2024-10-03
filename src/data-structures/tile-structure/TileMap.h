#ifndef IDLE_WIZARD_TILE_MAP_H
#define IDLE_WIZARD_TILE_MAP_H

#include <array>
#include <vector>
#include <unordered_set>
#include <iostream>

inline constexpr const int COLUMNS = 1;
inline constexpr const int ROWS = 1;
struct TileMap{
    std::array<std::vector<int>, COLUMNS * ROWS> m_map;
    std::vector<int> entities;

    const int tileWidth;
    const int tileHeight;

    //todo need to handle entities creation
    TileMap(const int tileWidth, const int tileHeight, const int initEntities) : tileWidth(tileWidth), tileHeight(tileHeight), entities(initEntities) {
    }

    void clear() {
        for (int i = 0; i < m_map.size(); ++i) {
            m_map[i].clear();
        }
    }

    void setEntitiesSize(size_t size){
        entities.resize(size);
    }

    void add(const int id, const int x, const int y, const int width, const int height) {
        int gridX = x / tileWidth;
        int gridY = y / tileHeight;

        int worldIndex = gridY * COLUMNS + gridX;
        m_map[worldIndex].emplace_back(id);
    }

    void entityAdd(){
      for(int i = 0; i < entities.size(); ++i){
       int worldIndex = entities[i];

       //TODO REMOVE THIS WHEN DONE TESTING
       if(worldIndex < 0 || worldIndex > (COLUMNS * ROWS)){
        std::cerr << "WorldIndex is Wrong: " << worldIndex << "\n"; 
        return;
       }

       m_map[worldIndex].emplace_back(i);
      }
    }

    void search(std::vector<int> &out,
                const float x,
                const float y,
                const float width,
                const float height) {
        const int minGridX = static_cast<int>(x / tileWidth);
        const int minGridY = static_cast<int>(y / tileHeight);
        const int maxGridX = static_cast<int>((x + width) / tileWidth);
        const int maxGridY = static_cast<int>((y + height) / tileHeight);

        for (int gridY = minGridY; gridY <= maxGridY; ++gridY) {
            for (int gridX = minGridX; gridX <= maxGridX; ++gridX) {
                const int worldIndex = gridY * COLUMNS + gridX;
                for (int i = 0; i < m_map[worldIndex].size(); ++i) {
                    out.emplace_back(m_map[worldIndex][i]);
                }
            }
        }
    }
};

#endif
