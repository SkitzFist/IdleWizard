#include "QuadTreeVisualizer.h"

#include <cmath>
#include <iostream>

QuadTreeVisualizer::QuadTreeVisualizer(int maxDepthLevel) {
    m_maxDepthLevel = maxDepthLevel;
    m_maxQuads = pow(4, m_maxDepthLevel);
    m_rootSize = 500.f;

    float currentSize = m_rootSize;
    int currentDepth = 0;
    int maxDepthAdds = 0;

    for (int i = 0; i < m_maxQuads; ++i) {
        if (currentDepth > 0) {
            int totalNumberOfQuads = pow(4, currentDepth);
            int quadWidth = sqrt(quadWidth);
            currentSize = m_rootSize / quadWidth;
        }

        // std::cout << "index: " << i << "  Current depth: " << currentDepth << "  Size: " << currentSize << '\n';

        m_rects.push_back(Rectangle{0, 0, currentSize, currentSize});
        m_depthLevels.push_back(currentDepth);

        if (currentDepth == m_maxDepthLevel) {
            ++maxDepthAdds;
        }

        if (currentDepth == m_maxDepthLevel && maxDepthAdds == 4) {
            maxDepthAdds = 0;
            --currentDepth;
        } else if (currentDepth < m_maxDepthLevel) {
            ++currentDepth;
        }
    }

    /*
    std::cout << "\n\n";
    for (size_t i = 0; i < m_depthLevels.size(); ++i) {
        std::cout << "Index: " << i << "  lvl: " << m_depthLevels[i] << "  size: " << m_rects[i].width << '\n';
    }
    */
}

void QuadTreeVisualizer::render() const {

    renderTreeWithDepthSplit();

    /*
    for (int i = 0; i <= m_maxDepthLevel; ++i) {
        renderDepth(i);
    }
    */
}

void QuadTreeVisualizer::renderTreeWithDepthSplit() const {
    float currentSize = m_rootSize;
    int currentDepth = 0;
    int maxDepthsCounter = 0; // on bottom layer, should draw 4 quads before going up a layer

    std::vector<float> currentXs(m_maxDepthLevel);
    std::vector<float> currentYs(m_maxDepthLevel);

    for (int i = 0; i < m_maxQuads; ++i) {
        if (currentDepth > 0) {
            int totalNumberOfQuads = pow(4, currentDepth);
            int quadWidth = sqrt(quadWidth);
            currentSize = m_rootSize / quadWidth;
        }
    }
}

void QuadTreeVisualizer::renderDepth(int depth) const {
    int quads = pow(4, depth);
    int width = sqrt(quads);

    float size = m_rootSize / width;
    std::cout << "depth: " << depth << " size: " << size << '\n';
    float padding = 25.f;
    float startX = (depth * m_rootSize) + (padding * depth);
    float startY = 500.f;

    float currentX = startX;
    float currentY = startY;

    for (int i = 0; i < quads; ++i) {
        float x = currentX;
        float y = currentY;

        DrawRectangleLines(x, y, size, size, RAYWHITE);
        currentX += size;

        if ((i + 1) % width == 0) {
            currentY += size;
            currentX = startX;
        }
    }
}