#include "TileStructure.h"

#include <cmath>

// debug
#include "raylib.h"
#include <iostream>
#include <string>

TileStructure::TileStructure(const float tileWidth,
                             const float tileHeight,
                             const int rows,
                             const int columns) : m_tileWidth(tileWidth),
                                                  m_tileHeight(tileHeight),
                                                  m_growthRate(2),
                                                  m_rows(rows),
                                                  m_columns(columns),
                                                  m_totalNumberOfTiles(0) {
    // init
    int initTiles = m_columns * m_rows;

    for (int i = 0; i < initTiles; ++i) {
        m_tiles.emplace_back();
        m_colors.emplace_back(RAYWHITE);
        ++m_totalNumberOfTiles;
    }
}

float TileStructure::currentMaxWidth() const {
    return static_cast<float>(m_columns * m_tileWidth);
}

float TileStructure::prevMaxWidth() const {
    return static_cast<float>((m_columns - m_growthRate) * m_tileWidth);
}

float TileStructure::currentMaxHeight() const {
    return static_cast<float>(m_rows * m_tileHeight);
}

float TileStructure::prevMaxHeight() const {
    return static_cast<float>((m_rows - m_growthRate) * m_tileHeight);
}

void TileStructure::growColumns() {
    m_columns += m_growthRate;

    size_t totalNumberOfTiles = m_columns * m_rows;
    size_t diff = totalNumberOfTiles - m_tiles.size();
    for (size_t i = 0; i < diff; ++i) {
        m_tiles.emplace_back();
        m_colors.emplace_back(RAYWHITE);
        ++m_totalNumberOfTiles;
    }
}

void TileStructure::addEntity(const int entityId, const float x, const float y, float width, float height) {
    IteratingProperties it = getIteratingProperties(x, y, width, height);

    // add entity to each tile it touches
    for (int yIndex = it.startIndex; yIndex <= it.yEndIndex; yIndex += m_columns) {
        for (int xOffset = 0; xOffset <= it.xLength; ++xOffset) {
            int index = yIndex + xOffset;

            if (index < 0 || index >= m_totalNumberOfTiles) {
                continue;
            }

            m_tiles[index].entities.emplace_back(entityId);
        }
    }
}

void TileStructure::search(const float x, const float y, const float width, const float height, std::unordered_set<int> &out) {
    for (size_t i = 0; i < m_colors.size(); ++i) {
        m_colors[i] = RAYWHITE;
    }

    IteratingProperties it = getIteratingProperties(x, y, width, height);

    for (int yIndex = it.startIndex; yIndex <= it.yEndIndex; yIndex += m_columns) {
        for (int xOffset = 0; xOffset <= it.xLength; ++xOffset) {
            int index = yIndex + xOffset;

            if (index < 0 || index >= m_totalNumberOfTiles) {
                continue;
            }

            m_colors[index] = YELLOW;
            for (size_t entity = 0; entity < m_tiles[index].entities.size(); ++entity) {
                out.emplace(m_tiles[index].entities[entity]);
            }
        }
    }
}

TileStructure::IteratingProperties TileStructure::getIteratingProperties(const float x, const float y, const float width, const float height) {
    const float invTileWidth = 1.f / m_tileWidth;
    const float invTileHeight = 1.f / m_tileHeight;

    const int startTileX = static_cast<int>(std::floor(x * invTileWidth));
    const int startTileY = static_cast<int>(std::floor(y * invTileHeight));
    const int endTileX = static_cast<int>(std::floor((x + width) * invTileWidth));
    const int endTileY = static_cast<int>(std::floor((y + height) * invTileHeight));

    const int startIndex = startTileY * m_columns + startTileX;
    const int xEndIndex = startTileY * m_columns + endTileX;
    const int xLength = xEndIndex - startIndex;
    const int yEndIndex = endTileY * m_columns + startTileX;

    return IteratingProperties{startIndex, xLength, yEndIndex};
}

void TileStructure::clear() {
    for (size_t tile = 0; tile < m_tiles.size(); ++tile) {
        m_tiles[tile].entities.clear();
    }
}

void TileStructure::debugRender() const {
    int id = 0;
    for (int y = 0; y < m_rows; ++y) {
        for (int x = 0; x < m_columns; ++x) {
            DrawRectangleLines(m_tileWidth * x,
                               m_tileHeight * y,
                               m_tileWidth,
                               m_tileHeight,
                               m_colors[y * m_columns + x]);

            DrawText(std::to_string(id).c_str(),
                     m_tileWidth * x + (m_tileWidth / 2.f),
                     m_tileHeight * y + (m_tileHeight / 2.f),
                     25,
                     RAYWHITE);
            ++id;
        }
    }
}