#include "QuadTreeTestState.h"

#include <iostream>
#include <string>

constexpr const int NUM_ENTITIES = 50;
constexpr const float WORLD_SIZE = 1000.f;
constexpr const int MAX_DEPTH = 5;
int numEntities = 0;

constexpr const float CIRCLE_MAX_SIZE = 50.f;

QuadTreeTestState::QuadTreeTestState() : m_camera(), m_quadTree(MAX_DEPTH, WORLD_SIZE) {
    m_camera.offset = {0, 0};
    m_camera.target = {0, 0};
    m_camera.rotation = 0.f;
    m_camera.zoom = 1.f;

    // create circle texture
    RenderTexture2D target = LoadRenderTexture(CIRCLE_MAX_SIZE * 2.f, CIRCLE_MAX_SIZE * 2.f);
    BeginTextureMode(target);
    ClearBackground(BLANK);
    DrawCircle(CIRCLE_MAX_SIZE, CIRCLE_MAX_SIZE, CIRCLE_MAX_SIZE, WHITE);
    EndTextureMode();
    m_circleTexture = target.texture;

    // add entities to quadtree
    for (int i = 0; i < NUM_ENTITIES; ++i) {
        createEntity();
    }
}

QuadTreeTestState::~QuadTreeTestState() {
}

void QuadTreeTestState::createEntity() {
    float min = 50.f;
    float max = WORLD_SIZE - 50.f;
    float x = static_cast<float>(GetRandomValue(min, max));
    float y = static_cast<float>(GetRandomValue(min, max));
    float size = static_cast<float>(GetRandomValue(4, CIRCLE_MAX_SIZE));
    float velX = static_cast<float>(GetRandomValue(-500.f, 500.f));
    float velY = static_cast<float>(GetRandomValue(-500.f, 500.f));
    int i = numEntities;
    m_positions.add(i, x, y);
    m_sizes.add(i, size);
    m_velocities.add(velX, velY);

    m_quadTree.addEntity(i, x, y, size * 2.f, size * 2.f);
    ++numEntities;
}

void QuadTreeTestState::handleInput() {
    m_cameraInput.handleInput(m_camera);

    if (IsKeyPressed(KEY_SPACE)) {
        for (int i = 0; i < 10; ++i) {
            createEntity();
        }
    }
}

void QuadTreeTestState::update(float dt) {
    m_quadTree.clearEntities();

    for (int i = 0; i < numEntities; ++i) {
        const float size = m_sizes.radiuses[i];
        m_quadTree.addEntity(
            i,
            m_positions.xPositions[i],
            m_positions.yPositions[i],
            size * 2.f,
            size * 2.f);
    }

    /*
        for (int entity = 0; entity < numEntities; ++entity) {
            m_positions.xPositions[entity] += (m_velocities.velX[entity] * dt);
            m_positions.yPositions[entity] += (m_velocities.velY[entity] * dt);
        }

        for (int entity = 0; entity < numEntities; ++entity) {
            if (m_positions.xPositions[entity] - m_sizes.radiuses[entity] < 0 ||
                m_positions.xPositions[entity] + m_sizes.radiuses[entity] > WORLD_SIZE) {
                m_velocities.velX[entity] *= -1.f;
            }
        }

        for (int entity = 0; entity < numEntities; ++entity) {
            if (m_positions.yPositions[entity] - m_sizes.radiuses[entity] < 0 ||
                m_positions.yPositions[entity] + m_sizes.radiuses[entity] > WORLD_SIZE) {
                m_velocities.velY[entity] *= -1.f;
            }
        }
        */
}

void QuadTreeTestState::render() const {
    BeginMode2D(m_camera);
    DrawRectangleLines(0, 0, m_quadTree.ROOT_SIZE, m_quadTree.ROOT_SIZE, RAYWHITE);
    m_quadTree.debugRenderSplit(m_positions, m_sizes, m_circleTexture);

    for (int entity = 0; entity < numEntities; ++entity) {
        float scale = m_sizes.radiuses[entity] / CIRCLE_MAX_SIZE;
        DrawTextureEx(
            m_circleTexture,
            {m_positions.xPositions[entity], m_positions.yPositions[entity]},
            0.f,
            scale,
            RED);
    }

    EndMode2D();
    drawUi();
}

void QuadTreeTestState::drawUi() const {
    const float x = 30.f;

    const float yOffset = 30.f;
    float y = 30.f;
    int fontSize = 20;

    std::string fpsText = "Fps: " + std::to_string(GetFPS());
    DrawText(fpsText.c_str(), x, y, fontSize, RAYWHITE);

    y += yOffset;
    std::string numEntitiesText = "Entities: " + std::to_string(numEntities);
    DrawText(numEntitiesText.c_str(), x, y, fontSize, RAYWHITE);
}
