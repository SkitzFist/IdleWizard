#include "TiledDataOrientedQuadTree.h"

#include <cmath>

#include "MathHack.hpp"

// debug
#include "raylib.h"
#include <iostream>

TiledDataOrientedQuadTree::TiledDataOrientedQuadTree(int maxDepth, const float rootSize) : MAX_DEPTH(maxDepth), ROOT_SIZE(rootSize),
                                                                                           m_currentDepth(0) {
    for (int depth = 0; depth <= 0; ++depth) {
        const int maxNumQuads = MathHack::pow(4, depth);
        m_depths.emplace_back(std::make_unique<Depth>(maxNumQuads));

        const int depthWidth = sqrt(maxNumQuads);
        m_numberOfQuadsOnSide.emplace_back(depthWidth);

        const int quadSize = rootSize / depthWidth;
        m_quadSize.emplace_back(quadSize);
    }
}

void TiledDataOrientedQuadTree::split() {
    ++m_currentDepth;

    const int maxNumQuads = MathHack::pow(4, m_currentDepth);
    m_depths.emplace_back(std::make_unique<Depth>(maxNumQuads));

    const int depthWidth = sqrt(maxNumQuads);
    m_numberOfQuadsOnSide.emplace_back(depthWidth);

    const int quadSize = ROOT_SIZE / depthWidth;
    m_quadSize.emplace_back(quadSize);
}

void TiledDataOrientedQuadTree::addEntity(int entity, float x, float y, float width, float height) {

    int depthLevel = m_currentDepth;

    for (int depth = m_currentDepth; depth >= 0; --depth) {
        // todo should check if should split and should change criteria for splitting
        if (width < m_quadSize[depth]) {
            depthLevel = depth;
            break;
        }
    }

    int index = 0;
    if (depthLevel > 0) {
        float quadX = x / m_quadSize[depthLevel];
        float quadY = y / m_quadSize[depthLevel];
        index = static_cast<int>(quadY * m_numberOfQuadsOnSide[depthLevel] + quadX);
    }

    m_depths[depthLevel]->quads[index]->entities.emplace_back(entity);
}

// todo addTile

void TiledDataOrientedQuadTree::getEntities(float x, float y, float width, float height, std::vector<int> &out) {
}

void TiledDataOrientedQuadTree::clearEntities() {
    for (int depth = 0; depth <= m_currentDepth; ++depth) {
        for (size_t quad = 0; quad < m_depths[depth]->quads.size(); ++quad) {
            m_depths[depth]->quads[quad]->entities.clear();
        }
    }
}

/////////////////////////////////////////////////
///              DEBUG                        ///
/////////////////////////////////////////////////

void TiledDataOrientedQuadTree::debugAdd(int entity, float x, float y, int depth) {
    float quadX = x / m_quadSize[depth];
    float quadY = y / m_quadSize[depth];
    int index = static_cast<int>(quadY * m_numberOfQuadsOnSide[depth] + quadX);
    std::cout << "depth: " << depth << "  index: " << index << '\n';
    m_depths[depth]->quads[index]->entities.emplace_back(entity);
}

void TiledDataOrientedQuadTree::debugRenderSplit(const Positions &positions, const Sizes &sizes, const Texture2D &texture) const {
    // draw split up quadTree
    for (int depth = 0; depth <= m_currentDepth; ++depth) {
        const float padding = 10.f;
        const float startX = (ROOT_SIZE * depth) + (padding * depth);
        const float startY = ROOT_SIZE * 1.25f;
        const float size = m_quadSize[depth];
        const float numQuadsOnSide = m_numberOfQuadsOnSide[depth];

        // draw horizontalLines
        for (int y = 0; y <= numQuadsOnSide; ++y) {
            float x1 = startX;
            float y1 = startY + (y * size);

            float x2 = x1 + size;
            float y2 = y1;

            DrawLine(x1, y1, x2, y2, RAYWHITE);
        }

        // draw vertical lines
        for (int x = 0; x <= numQuadsOnSide; ++x) {
            float x1 = startX + (size * x);
            float y1 = startY;

            float x2 = x1;
            float y2 = y1 + size;

            DrawLine(x1, y1, x2, y2, RAYWHITE);
        }

        // draw entities

        for (size_t quad = 0; quad < m_depths[depth]->quads.size(); ++quad) {
            for (const int entity : m_depths[depth]->quads[quad]->entities) {
                float scale = sizes.radiuses[entity] / 50.f;
                float x = startX + positions.xPositions[entity];
                float y = startY + positions.yPositions[entity];
                DrawTextureEx(
                    texture,
                    {x, y},
                    0.f,
                    scale,
                    RED);
            }
        }
    }
}
