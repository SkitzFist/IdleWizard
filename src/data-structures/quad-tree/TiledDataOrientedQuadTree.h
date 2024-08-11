#ifndef IDLE_MINER_TILED_DATA_ORIENTED_QUAD_TREE_H
#define IDLE_MINER_TILED_DATA_ORIENTED_QUAD_TREE_H

#include <memory>
#include <vector>

// debug
#include "Positions.h"
#include "Sizes.h"
#include "raylib.h"

struct Quad {
    std::vector<int> entities;
    // std::vector<int> tiles; TODO
};

struct Depth {
    std::vector<std::unique_ptr<Quad>> quads;
    Depth(int numQuads) {
        quads.reserve(numQuads);
        for (int i = 0; i < numQuads; ++i) {
            quads.emplace_back(std::make_unique<Quad>());
        }
    }
};

class TiledDataOrientedGrid {
  public:
    TiledDataOrientedGrid(int maxDepth, int startDepth, const float rootSize);

    void addEntity(int entity, float x, float y, float width, float height);
    // void addTile() TODO
    void getEntities(const float x,
                     const float y,
                     const float width,
                     const float height,
                     std::vector<int> &out,
                     const std::vector<float> &xPos,
                     const std::vector<float> &yPos,
                     const std::vector<float> &radiuses);

    void clearEntities();

    // debug
    void debugRender(const std::vector<float> &xPos,
                     const std::vector<float> &yPos,
                     const std::vector<float> &radiuses,
                     const Texture2D &circleTexture) const;

    const float ROOT_SIZE;

  private:
    unsigned short m_currentDepth;
    int m_totalNumberOfQuads;
    unsigned short m_numberOfQuadsOnSide; // the number of quads on x or y axis
    float m_quadSize;                     // the width of one quad
    std::vector<Quad> m_quads;
};

#endif
