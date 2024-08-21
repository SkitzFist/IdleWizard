#ifndef TESTS_COMPONENT_TEST
#define TESTS_COMPONENT_TEST

#include <iostream>
#include <vector>

#include "raylib.h"

#include "VectorComponent.h"
#include "VectorComponentUtils.h"

namespace ComponentTest {

enum EntityType {
    BLOB,
    TREE
};

enum Components {
    POSITION,
    VELOCITY
};

inline bool isVectorSorted(const std::vector<int> &v) {
    for (std::size_t i = 0; i < v.size() - 1; ++i) {
        if (v[i] > v[i + 1]) {
            std::cerr << "Vector is not sorted\n";
            return false;
        }
    }
    return true;
}

inline void printC(const VectorComponent &c) {
    for (size_t i = 0; i < c.entityIds.size(); ++i) {
        std::cout << "[" << i << "]: " << c.entityIds[i] << "  data: " << c.data[i].x << " . " << c.data[i].y << '\n';
    }
}

inline void sortElement(VectorComponent &c, int index) {
    if (index < 0 || index >= c.entityIds.size())
        return;

    int newIndex = index;

    // Move the element downwards if necessary
    while (newIndex > 0 && c.entityIds[newIndex] < c.entityIds[newIndex - 1]) {
        std::swap(c.entityIds[newIndex], c.entityIds[newIndex - 1]);
        std::swap(c.data[newIndex], c.data[newIndex - 1]);
        --newIndex;
    }

    // Move the element upwards if necessary
    while (newIndex < c.entityIds.size() - 1 && c.entityIds[newIndex] > c.entityIds[newIndex + 1]) {
        std::swap(c.entityIds[newIndex], c.entityIds[newIndex + 1]);
        std::swap(c.data[newIndex], c.data[newIndex + 1]);
        ++newIndex;
    }
}

inline bool oneTypeRemove() {
    int numEntities = 1000000;
    std::vector<EntityType> manager;

    VectorComponent positions;
    VectorComponent velocities;

    for (int i = 0; i < numEntities; ++i) {
        manager.push_back(BLOB);
        positions.add(i, (float)GetRandomValue(0, 100), (float)GetRandomValue(0, 100));
        velocities.add(i, (float)GetRandomValue(-10, 10), (float)GetRandomValue(-10, 10));
    }

    int numRemove = numEntities / 2;

    for (int i = 0; i < numRemove; ++i) {

        int index = GetRandomValue(0, manager.size() - 1);

        swapDataThenPop(positions, index);
        swapDataThenPop(velocities, index);
        manager.pop_back();
    }

    if (!isVectorSorted(positions.entityIds) || !isVectorSorted(velocities.entityIds)) {
        std::cerr << "TEST FAILED" << '\n';
        std::cerr << "Size: " << manager.size() << '\n';
        return false;
    }

    return true;
};

inline bool mixedEntityTest() {
    int numEntities = 100000;
    std::vector<EntityType> manager;

    VectorComponent positions;
    VectorComponent velocities;

    for (int i = 0; i < numEntities; ++i) {
        if (i % 2 == 0) {
            manager.push_back(BLOB);
            positions.add(i, (float)GetRandomValue(0, 100), (float)GetRandomValue(0, 100));
            velocities.add(i, (float)GetRandomValue(-10, 10), (float)GetRandomValue(-10, 10));
        } else {
            manager.push_back(TREE);
            positions.add(i, (float)GetRandomValue(0, 100), (float)GetRandomValue(0, 100));
        }
    }

    // std::cout << "Manager:\n";
    // int indexType = 0;
    // for (const EntityType type : manager) {
    //     std::cout << "[" << indexType << "]: " << (type == BLOB ? "BLOB" : "TREE") << '\n';
    // }
    // std::cout << "Position:\n";
    // printC(positions);
    // std::cout << "Velocities:\n";
    // printC(velocities);

    int numRemove = numEntities / 2;

    for (int i = 0; i < numRemove; ++i) {
        int id = GetRandomValue(0, manager.size() - 1);
        int lastId = manager.size() - 1;
        EntityType typeA = manager[id];
        EntityType typeB = manager[lastId];

        // std::cout << "\nA: " << typeA << "  B: " << typeB << '\n';

        if (!isVectorSorted(positions.entityIds) || !isVectorSorted(velocities.entityIds)) {
            std::cerr << "TEST FAILED" << '\n';
            std::cerr << "Index: " << id << '\n';
            std::cerr << "Size: " << manager.size() << '\n';
            return false;
        }

        if (typeA == typeB) {
            swapDataThenPop(positions, id);
            if (typeA == BLOB) {
                swapDataThenPop(velocities, id);
            }

            manager.pop_back();
        } else if (typeA == TREE && typeB == BLOB) {
            swapDataThenPop(positions, id);
            switchId(velocities, lastId, id);
            std::swap(manager[id], manager[lastId]);
            manager.pop_back();
        } else if (typeA == BLOB && typeB == TREE) {
            swapDataThenPop(positions, id);
            swapDataAndIdThenPop(velocities, id);
            std::swap(manager[id], manager[lastId]);
            manager.pop_back();
        }

        if (!isVectorSorted(positions.entityIds) || !isVectorSorted(velocities.entityIds)) {
            std::cerr << "TEST FAILED" << '\n';
            std::cerr << "Index: " << id << '\n';
            std::cerr << "Size: " << manager.size() << '\n';
            return false;
        }

        // std::cout << "Manager:\n";
        // int indexType = 0;
        // for (const EntityType type : manager) {
        //     std::cout << "[" << indexType << "]: " << (type == BLOB ? "BLOB" : "TREE") << '\n';
        // }
        // std::cout << "Position:\n";
        // printC(positions);
        // std::cout << "Velocities:\n";
        // printC(velocities);
    }

    return true;
}

inline bool runComponentTests() {
    // if (!oneTypeRemove()) {
    //     std::cout << "OneTypeRemove failed\n";
    //     return false;
    // }

    if (!mixedEntityTest()) {
        return false;
    }

    return true;
}

}; // namespace ComponentTest

#endif