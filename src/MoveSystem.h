#ifndef IDLE_MINER_MOVE_SYSTEM_H
#define IDLE_MINER_MOVE_SYSTEM_H

#include "Component.h"
#include "ComponentUtils.h"

#include "Timer.h"

inline void moveEntities(Component &positions, const Component &velocities, const float dt) {
    for (int i = 0; i < velocities.size; ++i) {
        int positionIndex = getIndex(positions, velocities.entityIds[i]);
        accessData<Vector2>(positions, positionIndex).x += (readData<Vector2>(velocities, i).x * dt);
        accessData<Vector2>(positions, positionIndex).y += (readData<Vector2>(velocities, i).y * dt);
    }
}

inline void bounceOnEdge(const Component &positions, const Component &sizes, Component &velocities, const float maxX, const float maxY) {
    Vector2 pos = {0.f, 0.f};
    Vector2 size{0.f, 0.f};
    int posIndex = 0;
    int sizeIndex = 0;

    for (int id = 0; id < velocities.size; ++id) {
        posIndex = getIndex(positions, velocities.entityIds[id]);
        sizeIndex = getIndex(sizes, velocities.entityIds[id]);
        pos = readData<Vector2>(positions, posIndex);
        size = readData<Vector2>(sizes, sizeIndex);

        int condition = (pos.x < 0.f || pos.x + size.x > maxX);
        accessData<float>(velocities, id, 0) *= 1.f - 2.f * condition;

        condition = (pos.y < 0.f || pos.y + size.y > maxY);
        accessData<float>(velocities, id, 1) *= 1.f - 2.f * condition;
    }
}

#endif
