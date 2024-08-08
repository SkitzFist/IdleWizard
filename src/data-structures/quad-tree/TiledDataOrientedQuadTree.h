#ifndef IDLE_MINER_TILED_DATA_ORIENTED_QUAD_TREE_H
#define IDLE_MINER_TILED_DATA_ORIENTED_QUAD_TREE_H

#include <memory>
#include <vector>

// debug
#include "Positions.h"
#include "Sizes.h"
#include "raylib.h"

/*
  Todo should remove the depth, only one layer allowed at a time.
*/

struct Quad {
    std::vector<int> entities;
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

class TiledDataOrientedQuadTree {
  public:
    TiledDataOrientedQuadTree(int maxDepth, const float rootSize);

    void addEntity(int entity, float x, float y, float width, float height);
    // void addTile() TODO
    void getEntities(float x, float y, float width, float height, std::vector<int> &out);

    void clearEntities();

    // debug
    void debugAdd(int entity, float x, float y, int depth);
    void debugRenderSplit(const Positions &positions, const Sizes &sizes, const Texture2D &texture) const;

    const float ROOT_SIZE;

  private:
    const int MAX_DEPTH;
    int m_currentDepth;
    std::vector<float> m_numberOfQuadsOnSide; // the number of quads on x or y axis
    std::vector<float> m_quadSize;            // the width of one quad
    std::vector<int> m_numEntitiesAtDepth;
    std::vector<std::unique_ptr<Depth>> m_depths;

  private:
    void split();
};

#endif
