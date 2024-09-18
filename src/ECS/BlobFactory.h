#ifndef IDLE_MINER_BLOB_FACTORY_H
#define IDLE_MINER_BLOB_FACTORY_H

#include "ComponentManager.h"
#include "ComponentType.h"
#include "EntityManager.h"
#include "EntityType.h"

#include "Component.h"
#include "ComponentUtils.h"

#include "TileStructure.h"

//debug
#include <iostream>

inline constexpr const float BLOB_WIDTH = 50.f;
inline constexpr const float BLOB_HEIGHT = 50.f;

inline const void createBlobAt(EntityManager &entityManager,
                             ComponentManager &componentManager,
                             Component &positions,
                             Component &sizes,
                             Component &velocities,
                             float x,
                             float y) {

    int entityId = entityManager.createEntity(EntityType::BLOB);
    componentManager.createEntity();

    add(positions, entityId, Vector2{x, y});
    componentManager.addComponentToEntity(entityId, ComponentType::POSITION);

    add(sizes, entityId, Vector2{BLOB_WIDTH, BLOB_HEIGHT});
    componentManager.addComponentToEntity(entityId, ComponentType::SIZE);

    float velX = static_cast<float>(GetRandomValue(-200, 200));
    float velY = static_cast<float>(GetRandomValue(-200, 200));
    add(velocities, entityId, Vector2{velX, velY});
    componentManager.addComponentToEntity(entityId, ComponentType::VELOCITY);
}

inline const void createBlobAt(EntityManager &entityManager,
                               ComponentManager &componentManager,
                               float x,
                               float y) {
    int entityId = entityManager.createEntity(EntityType::BLOB);
    componentManager.createEntity();

    add(componentManager.components[ComponentType::POSITION], entityId, Vector2{x, y});
    componentManager.addComponentToEntity(entityId, ComponentType::POSITION);

    add(componentManager.components[ComponentType::SIZE], entityId, Vector2{BLOB_WIDTH, BLOB_HEIGHT});
    componentManager.addComponentToEntity(entityId, ComponentType::SIZE);

    float velX = static_cast<float>(GetRandomValue(-200, 200));
    float velY = static_cast<float>(GetRandomValue(-200, 200));
    add(componentManager.components[ComponentType::VELOCITY], entityId, Vector2{velX, velY});
    componentManager.addComponentToEntity(entityId, ComponentType::VELOCITY);
}

#endif
