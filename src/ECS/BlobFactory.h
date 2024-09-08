#ifndef IDLE_MINER_BLOB_FACTORY_H
#define IDLE_MINER_BLOB_FACTORY_H

#include "ComponentManager.h"
#include "ComponentType.h"
#include "EntityManager.h"
#include "EntityType.h"

#include "Component.h"
#include "ComponentUtils.h"

#include "TileStructure.h"

inline constexpr const float BLOB_WIDTH = 50.f;
inline constexpr const float BLOB_HEIGHT = 50.f;

inline const void createBlob(EntityManager &entityManager,
                             ComponentManager &componentManager,
                             Component &positions,
                             Component &sizes,
                             Component &velocities,
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
    add(positions, entityId, Vector2{x, y});
    componentManager.addComponent(entityId, ComponentType::POSITION);

    add(sizes, entityId, Vector2{BLOB_WIDTH, BLOB_HEIGHT});
    componentManager.addComponent(entityId, ComponentType::SIZE);

    float velX = static_cast<float>(GetRandomValue(-200, 200));
    float velY = static_cast<float>(GetRandomValue(-200, 200));
    add(velocities, entityId, Vector2{velX, velY});
    componentManager.addComponent(entityId, ComponentType::VELOCITY);
}

#endif
