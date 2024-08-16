#include "EcsTestState.h"

#include <iostream>

#include "BlobFactory.h"
#include "TreeFactory.h"

EcsTestState::EcsTestState(const GameOptions &gameOptions) : m_tileStructure(gameOptions.SCREEN_WIDTH, gameOptions.SCREEN_HEIGHT, 1, 1) {
    m_camera.offset = {0.f, 0.f};
    m_camera.target = {0.f, 0.f};
    m_camera.rotation = 0.f;
    m_camera.zoom = 1.f;

    registerComponents();

    for (int i = 0; i < 10; ++i) {
        if (i % 3 != 0) {
            createBlob(m_entityManager, m_componentManager, m_positions, m_sizes, m_velocities, m_tileStructure, 0.f, 0.f);
        } else {
            createTree(m_entityManager, m_componentManager, m_positions, m_sizes, m_tileStructure, 0.f, 0.f);
        }
    }
}

EcsTestState::~EcsTestState() {
}

void EcsTestState::registerComponents() {
    m_componentManager.registerVectorComponent(POSITION, &m_positions);
    m_componentManager.registerVectorComponent(SIZE, &m_sizes);
    m_componentManager.registerVectorComponent(VELOCITY, &m_velocities);
}

void EcsTestState::handleInput() {
    m_cameraInput.handleInput(m_camera);

    if (IsKeyPressed(KEY_SPACE)) {
        int index = GetRandomValue(0, (int)m_entityManager.getNumEntities() - 1);
        m_entityManager.destroyEntity(index, m_componentManager);
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int number = GetRandomValue(0, 100);
        if (number < 50) {
            createBlob(m_entityManager, m_componentManager, m_positions, m_sizes, m_velocities, m_tileStructure, 0.f, 0.f);
        } else {
            createTree(m_entityManager, m_componentManager, m_positions, m_sizes, m_tileStructure, 0.f, 0.f);
        }
    }
}

void EcsTestState::update(float dt) {
    /* Deletion test
    if (m_entityManager.entities.size() > 0) {
        int index = GetRandomValue(0, (int)m_entityManager.getNumEntities() - 1);
        m_entityManager.destroyEntity(index, m_componentManager);
    }
    */
}

void EcsTestState::render() const {

    BeginMode2D(m_camera);

    m_tileStructure.debugRender();

    int index = 0;
    for (const EntityType entityType : m_entityManager.entities) {
        switch (entityType) {
        case EntityType::BLOB:
            DrawRectangle(
                m_positions.data[index].x,
                m_positions.data[index].y,
                m_sizes.data[index].x,
                m_sizes.data[index].y,
                RED);
            break;

        case EntityType::TREE:
            DrawRectangle(
                m_positions.data[index].x,
                m_positions.data[index].y,
                m_sizes.data[index].x,
                m_sizes.data[index].y,
                BROWN);
            break;

        default:
            break;
        }

        ++index;
    }

    EndMode2D();
}

void EcsTestState::renderUi() const {
}
