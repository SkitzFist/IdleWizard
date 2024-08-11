#include "QuadTreeTestState.h"

#include <iostream>
#include <string>

constexpr const int NUM_ENTITIES = 1;
constexpr const float WORLD_SIZE = 1000.f;
constexpr const int MAX_DEPTH = 5;
int numEntities = 0;

constexpr const float CIRCLE_MAX_SIZE = 50.f;

QuadTreeTestState::QuadTreeTestState() : m_camera(),
                                         m_quadTree(MAX_DEPTH, 2, WORLD_SIZE),
                                         m_range{0.f, 0.f, 1000.f, 1000.f} {
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
    try {
        for (int i = 0; i < NUM_ENTITIES; ++i) {
            createEntity();
        }
    } catch (...) {
        std::cerr << "Error adding init entities" << '\n';
    }

    // debug
    SetRandomSeed(0);
}

QuadTreeTestState::~QuadTreeTestState() {
}

void QuadTreeTestState::createEntity() {
    float min = 50.f;
    float max = WORLD_SIZE - 50.f;
    float x = static_cast<float>(GetRandomValue(min, max));
    float y = static_cast<float>(GetRandomValue(min, max));
    float radius = static_cast<float>(GetRandomValue(4, CIRCLE_MAX_SIZE));
    float velX = static_cast<float>(GetRandomValue(-500.f, 500.f));
    float velY = static_cast<float>(GetRandomValue(-500.f, 500.f));
    int i = numEntities;
    m_positions.add(i, x, y);
    m_sizes.add(i, radius);
    m_velocities.add(velX, velY);
    m_quadTree.addEntity(i, x, y, radius, radius);
    ++numEntities;
}

Rectangle QuadTreeTestState::getCameraRect() const {
    Vector2 cameraPos = m_camera.target;
    Vector2 size = {GetScreenWidth() / m_camera.zoom, GetScreenHeight() / m_camera.zoom};
    return {cameraPos.x, cameraPos.y, size.x, size.y};
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
    // clear entities and re-add them to the quadtree
    m_quadTree.clearEntities();
    for (int i = 0; i < numEntities; ++i) {
        const float size = m_sizes.radiuses[i];
        m_quadTree.addEntity(
            i,
            m_positions.xPositions[i],
            m_positions.yPositions[i],
            size,
            size);
    }

    // get entities in camera range
    m_range = getCameraRect();
    m_entitiesInRange.clear();
    m_quadTree.getEntities(m_range.x,
                           m_range.y,
                           m_range.width,
                           m_range.height,
                           m_entitiesInRange,
                           m_positions.xPositions,
                           m_positions.yPositions,
                           m_sizes.radiuses);

    // move entities
    for (int entity = 0; entity < numEntities; ++entity) {
        m_positions.xPositions[entity] += (m_velocities.velX[entity] * dt);
        m_positions.yPositions[entity] += (m_velocities.velY[entity] * dt);
    }

    // check x bound
    for (int entity = 0; entity < numEntities; ++entity) {
        if (m_positions.xPositions[entity] < 0 ||
            m_positions.xPositions[entity] + (m_sizes.radiuses[entity] * 2.f) > WORLD_SIZE) {
            m_velocities.velX[entity] *= -1.f;
        }
    }

    // check y bound
    for (int entity = 0; entity < numEntities; ++entity) {
        if (m_positions.yPositions[entity] < 0 ||
            m_positions.yPositions[entity] + (m_sizes.radiuses[entity] * 2.f) > WORLD_SIZE) {
            m_velocities.velY[entity] *= -1.f;
        }
    }
}

void QuadTreeTestState::render() const {
    BeginMode2D(m_camera);
    // quadtree
    DrawRectangleLines(0, 0, m_quadTree.ROOT_SIZE, m_quadTree.ROOT_SIZE, RAYWHITE);
    // m_quadTree.debugRender(m_positions.xPositions, m_positions.yPositions, m_sizes.radiuses, m_circleTexture);

    // entities
    for (const int entity : m_entitiesInRange) {
        float scale = m_sizes.radiuses[entity] / CIRCLE_MAX_SIZE;
        DrawTextureEx(
            m_circleTexture,
            {m_positions.xPositions[entity], m_positions.yPositions[entity]},
            0.f,
            scale,
            RED);

        /* Draw bounding box
        DrawRectangleLines(m_positions.xPositions[entity],
                           m_positions.yPositions[entity],
                           m_sizes.radiuses[entity] * 2.f,
                           m_sizes.radiuses[entity] * 2.f,
                           GREEN);
        */
    }

    // Camera range
    DrawRectangleLinesEx(m_range, 10.f, YELLOW);

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
