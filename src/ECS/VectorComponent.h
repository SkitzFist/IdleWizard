#ifndef IDLE_MINER_VECTOR_COMPONENT_H
#define IDLE_MINER_VECTOR_COMPONENT_H

#include <vector>

#include "raylib.h"

// debug
#include <iostream>

struct VectorComponent {
    std::vector<Vector2> data;
    std::vector<int> entityIds;

    void add(const int id, const float x, const float y) {
        data.push_back({x, y});
        entityIds.emplace_back(id);
    }
};

#endif
