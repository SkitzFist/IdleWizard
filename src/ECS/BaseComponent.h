#ifndef IDLE_MINER_BASE_COMPONENT_H
#define IDLE_MINER_BASE_COMPONENT_H

#include <vector>

#include "raylib.h"

#include "ComponentType.h"

struct BaseComponent {
    std::vector<int> entityIds;
    ComponentType type;
};

struct Vector2Component : public BaseComponent {
    std::vector<Vector2> data;
    void add(const int id, const float x, const float y) {
        entityIds.emplace_back(id);
        data.push_back({x, y});
    }
    void reserve(int size) {
        entityIds.reserve(size);
        data.reserve(size);
    }
};

#endif
