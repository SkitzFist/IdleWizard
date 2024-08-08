#ifndef IDLE_MINER_POSITIONS_H_
#define IDLE_MINER_POSITIONS_H_

#include <vector>

struct Positions {
    std::vector<float> xPositions;
    std::vector<float> yPositions;

    void add(int entity, float x, float y) {
        xPositions.emplace_back(x);
        yPositions.emplace_back(y);
    }

    float getX(int entity) const {
        return xPositions[entity];
    }

    float getY(int entity) const {
        return yPositions[entity];
    }

    void remove(int entity) {
    }
};

#endif