#ifndef IDLE_MINER_BLOB_FACTORY_H
#define IDLE_MINER_BLOB_FACTORY_H

#include "ComponentManager.h"
#include "ComponentType.h"
#include "EntityManager.h"
#include "EntityType.h"

#include "VectorComponent.h"

#include "TileStructure.h"

inline constexpr const float BLOB_WIDTH = 50.f;
inline constexpr const float BLOB_HEIGHT = 50.f;

inline const void createBlob(EntityManager &entityManager,
                             ComponentManager &componentManager,
                             VectorComponent &positions,
                             VectorComponent &sizes,
                             VectorComponent &velocities,
                             TileStructure &tileStructure,
                             float minX,
                             float minY) {

    int entityId = entityManager.createEntity(EntityType::BLOB);
    componentManager.createEntity();

    float min = minX;
    float max = tileStructure.currentMaxWidth() - BLOB_WIDTH;
    float x = static_cast<float>(GetRandomValue(min, max));

    min = minY;
    max = tileStructure.currentMaxHeight() - BLOB_HEIGHT;
    float y = static_cast<float>(GetRandomValue(min, max));
    positions.add(entityId, x, y);
    componentManager.addComponent(entityId, ComponentType::POSITION);

    sizes.add(entityId, BLOB_WIDTH, BLOB_HEIGHT);
    componentManager.addComponent(entityId, ComponentType::SIZE);

    float velX = static_cast<float>(GetRandomValue(-200, 200));
    float velY = static_cast<float>(GetRandomValue(-200, 200));
    velocities.add(entityId, velX, velY);
    componentManager.addComponent(entityId, ComponentType::VELOCITY);
}

#endif
