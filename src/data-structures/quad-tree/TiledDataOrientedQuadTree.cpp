#include "TiledDataOrientedQuadTree.h"

#include <cmath>

#include "MathHack.hpp"

// debug
#include "raylib.h"
#include <iostream>

TiledDataOrientedGrid::TiledDataOrientedGrid(int maxDepth, int startDepth, const float rootSize) : ROOT_SIZE(rootSize),
                                                                                                   m_currentDepth(startDepth) {
    m_totalNumberOfQuads = MathHack::pow(4, m_currentDepth);
    m_numberOfQuadsOnSide = MathHack::pow(2, m_currentDepth);
    m_quadSize = ROOT_SIZE / m_numberOfQuadsOnSide;

    for (int i = 0; i < m_totalNumberOfQuads; ++i) {
        m_quads.emplace_back();
    }
}

void TiledDataOrientedGrid::addEntity(int entity, float x, float y, float width, float height) {

    if (x + width < 0.f || x > ROOT_SIZE || y + height < 0.f || y > ROOT_SIZE) {
        return;
    }

    float quadX = floor(abs(x) / m_quadSize);
    float quadY = floor(abs(y) / m_quadSize);
    int index = static_cast<int>(quadY * m_numberOfQuadsOnSide + quadX);

    m_quads[index].entities.emplace_back(entity);
}

// todo addTile

void TiledDataOrientedGrid::getEntities(const float x,
                                        const float y,
                                        const float width,
                                        const float height,
                                        std::vector<int> &out,
                                        const std::vector<float> &xPos,
                                        const std::vector<float> &yPos,
                                        const std::vector<float> &radiuses) {
    if (x + width < 0.f || x > ROOT_SIZE || y + height < 0.f || y > ROOT_SIZE) {
        return;
    }
    const float invQuadSize = 1.f / m_quadSize;
    const int startQuadX = static_cast<int>(std::floor(x * invQuadSize));
    const int startQuadY = static_cast<int>(std::floor(y * invQuadSize));
    const int endQuadX = static_cast<int>(std::ceil((x + width) * invQuadSize));
    const int endQuadY = static_cast<int>(std::ceil((y + height) * invQuadSize));

    int startIndex = static_cast<int>(startQuadY * m_numberOfQuadsOnSide + startQuadX);
    int xEndIndex = static_cast<int>(floor(startQuadY * m_numberOfQuadsOnSide + endQuadX));
    int xLength = xEndIndex - startIndex;
    int yEndIndex = static_cast<int>(endQuadY * m_numberOfQuadsOnSide + startQuadX);

    for (int yIndex = startIndex; yIndex <= yEndIndex; yIndex += m_numberOfQuadsOnSide) {
        for (int xOffset = 0; xOffset <= xLength; ++xOffset) {
            int index = yIndex + xOffset;
            if (index >= 0 && index < m_totalNumberOfQuads) {
                for (size_t entityIndex = 0; entityIndex < m_quads[index].entities.size(); ++entityIndex) {
                    out.emplace_back(m_quads[index].entities[entityIndex]);
                }
            }
        }
    }
}

void TiledDataOrientedGrid::clearEntities() {
    for (int i = 0; i < m_totalNumberOfQuads; ++i) {
        m_quads[i].entities.clear();
    }
}

/////////////////////////////////////////////////
///            DEPRECATED                     ///
/////////////////////////////////////////////////

/*
void TiledDataOrientedGrid::debugRender(const std::vector<float> &xPos,
                                        const std::vector<float> &yPos,
                                        const std::vector<float> &radiuses,
                                        const Texture2D &circleTexture) const {
    const float startX = 0.f;
    const float startY = ROOT_SIZE * 1.25f;

    // draw grid
    for (int y = 0; y < m_numberOfQuadsOnSide; ++y) {
        for (int x = 0; x < m_numberOfQuadsOnSide; ++x) {
            int index = y * m_numberOfQuadsOnSide + x;
            float quadX = startX + (m_quadSize * x);
            float quadY = startY + (m_quadSize * y);
            DrawRectangleLines(quadX, quadY, m_quadSize, m_quadSize, RAYWHITE);
        }
    }

    // draw entities
    for (int quad = 0; quad < m_totalNumberOfQuads; ++quad) {
        for (int entityIndex = 0; entityIndex < m_quads[quad].entities.size(); ++entityIndex) {
            float scale = radiuses[m_quads[quad].entities[entityIndex]] / 50.f;
            float x = startX + xPos[m_quads[quad].entities[entityIndex]];
            float y = startY + yPos[m_quads[quad].entities[entityIndex]];
            DrawTextureEx(
                circleTexture,
                {x, y},
                0.f,
                scale,
                RED);
        }
    }
}
*/