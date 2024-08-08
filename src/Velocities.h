#ifndef IDLE_MINER_VELOCITIES_H
#define IDLE_MINER_VELOCITIES_H

#include <vector>

struct Velocities {
    std::vector<float> velX;
    std::vector<float> velY;

    void add(float x, float y) {
        velX.emplace_back(x);
        velY.emplace_back(y);
    }
};

#endif
