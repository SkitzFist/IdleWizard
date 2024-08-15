#include "EcsTestState.h"

#include <iostream>

#include "BlobFactory.h"
#include "TreeFactory.h"

EcsTestState::EcsTestState() : m_tileStructure(1920, 1280, 1, 1) {
    m_camera.offset = {0.f, 0.f};
    m_camera.target = {0.f, 0.f};
    m_camera.rotation = 0.f;
    m_camera.zoom = 1.f;

    createBlob(m_entityManager, m_componentManager, m_positions, m_sizes, m_velocities, m_tileStructure, 0.f, 0.f);
    createTree(m_entityManager, m_componentManager, m_positions, m_sizes, m_tileStructure, 0.f, 0.f);
}

EcsTestState::~EcsTestState() {
}

void EcsTestState::handleInput() {
}

void EcsTestState::update(float dt) {
}

void EcsTestState::render() const {
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
}

void EcsTestState::renderUi() const {
}
