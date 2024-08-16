#ifndef IDLE_MINER_VECTOR_COMPONENT_H
#define IDLE_MINER_VECTOR_COMPONENT_H

#include <vector>

#include "raylib.h"

// debug
#include "EntityManager.h"
#include <iostream>

struct VectorComponent {
    std::vector<Vector2> data;
    std::vector<int> entityIds;

    void add(const int id, const float x, const float y) {
        data.push_back({x, y});
        entityIds.emplace_back(id);
    }

    int getindex(int id) const {
        for (std::size_t i = 0; i < entityIds.size(); ++i) {
            if (id == entityIds[i]) {
                return static_cast<int>(i);
            }
        }

        return -1;
    }

    void putHighestEntityAtBack() {
        int index = 0;
        for (size_t i = 0; i < entityIds.size(); ++i) {
            if (entityIds[index] < entityIds[i]) {
                index = i;
            }
        }

        std::swap(entityIds[index], entityIds.back());
        std::swap(data[index], data.back());
    }

    // both have component
    void SwapDataThenPop(int id) {

        // in order to avoid ID confusion, the entity with the highest id must be pushed to the back,
        // as we always delete from the bottom.
        putHighestEntityAtBack();

        int aIndex = getindex(id);

        if (aIndex == -1) {
            std::cerr << "VectorComponent: SWAP DATA & ID Returning index is -1\n";
            return;
        }

        // std::cout << "\tAindex: " << aIndex << "  BIndex: " << bIndex << '\n';
        std::swap(data[aIndex], data.back());
        data.pop_back();
        entityIds.pop_back();
    }

    // only A has component
    void swapDataAndIdThenPop(int id) {
        int aIndex = getindex(id);
        if (aIndex == -1) {
            std::cerr << "VectorComponent: SWAP DATA & ID Returning index is -1\n";
            return;
        }

        std::swap(data[aIndex], data.back());
        data.pop_back();

        std::swap(entityIds[aIndex], entityIds.back());
        entityIds.pop_back();
    }

    // only b has component
    void switchId(int from, int to) {
        size_t index = -1;
        for (std::size_t i = 0; i < entityIds.size(); ++i) {
            if (entityIds[i] == from) {
                entityIds[i] = to;
                index = i;
                break;
            }
        }

        if (index == -1) {
            std::cerr << "VectorComponent: Switch Id could not find id\n";
            return;
        }

        /* Leave if ever needed, moves entity up in the list as long as the previous entity has a higher index. Tested 10 times with 100k entities,
           Without any errors. But My gut feeling tells me this could be a problem in the future.
        size_t lowerIndex = index - 1;
        while (lowerIndex >= 0 && entityIds[index] < entityIds[lowerIndex]) {
            std::swap(entityIds[index], entityIds[lowerIndex]);
            std::swap(data[index], data[lowerIndex]);
            --index;
            --lowerIndex;
        }
        */
        // std::cout << "Switch Id could not find id\n";
    }

    void print(EntityManager &e) {
        for (size_t i = 0; i < entityIds.size(); ++i) {
            EntityType type = e.entities[entityIds[i]];
            std::cout << "[" << i << "]: " << entityIds[i] << "  Type: " << toString(type) << "  data: " << data[i].x << " . " << data[i].y << '\n';
        }
    }
};

#endif
