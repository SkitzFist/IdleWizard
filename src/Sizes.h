#ifndef IDLE_MINER_SIZES_H
#define IDLE_MINER_SIZES_H

#include <vector>

struct Sizes {
    std::vector<float> radiuses;

    void add(int entity, float radius) {
        radiuses.emplace_back(radius);
    }
};

#endif
