#ifndef IDLE_MINER_QUAD_TREE_VISUALIZER_H
#define IDLE_MINER_QUAD_TREE_VISUALIZER_H

#include <vector>

#include "raylib.h"

class QuadTreeVisualizer {
  public:
    QuadTreeVisualizer(int depthLevel);
    void render() const;

  private:
    int m_maxDepthLevel;
    int m_maxQuads;
    float m_rootSize;
    std::vector<Rectangle> m_rects;
    std::vector<int> m_depthLevels;

    void renderDepth(int depth) const;
};

#endif
