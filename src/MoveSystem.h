#ifndef IDLE_MINER_MOVE_SYSTEM_H
#define IDLE_MINER_MOVE_SYSTEM_h

#include "VectorComponent.h"
#include "VectorComponentUtils.h"

inline void moveEntities(VectorComponent &positions, const VectorComponent &velocities, const float dt) {
    int index = 0;
    for (const int id : velocities.entityIds) {
        int positionIndex = getIndex(positions, id);
        positions.data[positionIndex].x += (velocities.data[index].x * dt);
        positions.data[positionIndex].y += (velocities.data[index].y * dt);
        ++index;
    }
}

inline void bounceOnEdge(const VectorComponent &positions, const VectorComponent &sizes, VectorComponent &velocities, const float maxX, const float maxY) {
    int index = 0;

    for (const int id : velocities.entityIds) {
        int posIndex = getIndex(positions, id);
        int sizeIndex = getIndex(sizes, id);

        if (positions.data[posIndex].x < 0.f || positions.data[posIndex].x + sizes.data[sizeIndex].x > maxX) {
            velocities.data[index].x *= -1.f;
        }

        if (positions.data[posIndex].y < 0.f || positions.data[posIndex].y + sizes.data[sizeIndex].y > maxY) {
            velocities.data[index].y *= -1.f;
        }

        ++index;
    }
}

#endif
