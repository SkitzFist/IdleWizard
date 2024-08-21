#include "EcsTestState.h"

#include <iostream>

#include "BlobFactory.h"
#include "TreeFactory.h"

#include "MoveSystem.h"
#include "VectorComponentUtils.h"

#include "Timer.h"

Timer timer;

EcsTestState::EcsTestState(const GameOptions &gameOptions) : m_tileStructure(gameOptions.SCREEN_WIDTH, gameOptions.SCREEN_HEIGHT, 1, 10) {
    m_camera.offset = {0.f, 0.f};
    m_camera.target = {0.f, 0.f};
    m_camera.rotation = 0.f;
    m_camera.zoom = 1.f;

    // create blob texture
    const float blobSize = 50.f;
    RenderTexture2D target = LoadRenderTexture(blobSize, blobSize);
    BeginTextureMode(target);
    ClearBackground(BLANK);
    DrawRectangle(0.f, 0.f, blobSize, blobSize, WHITE);
    EndTextureMode();
    m_blobTexture = target.texture;

    // create tree texture
    const float treeWidth = 10.f;
    const float treeHeight = 250.f;
    target = LoadRenderTexture(treeWidth, treeHeight);

    BeginTextureMode(target);
    ClearBackground(BLANK);
    DrawRectangle(0.f, 0.f, treeWidth, treeHeight, WHITE);
    EndTextureMode();
    m_treeTexture = target.texture;

    registerComponents();

    for (int i = 0; i < 10000; ++i) {
        if (GetRandomValue(0, 100) > 50) {
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

    // remove random entity
    if (IsKeyPressed(KEY_SPACE)) {
        int index = GetRandomValue(0, (int)m_entityManager.getNumEntities() - 1);
        m_entityManager.destroyEntity(index, m_componentManager);
    }

    // spawn random entity
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int number = GetRandomValue(0, 100);
        if (number < 50) {
            createBlob(m_entityManager, m_componentManager, m_positions, m_sizes, m_velocities, m_tileStructure, 0.f, 0.f);
        } else {
            createTree(m_entityManager, m_componentManager, m_positions, m_sizes, m_tileStructure, 0.f, 0.f);
        }
    }

    setRange();
}

int tick = 0;

void EcsTestState::update(float dt) {

    // Deletion test
    // if (m_entityManager.entities.size() > 0) {
    //     int index = GetRandomValue(0, (int)m_entityManager.getNumEntities() - 1);
    //     m_entityManager.destroyEntity(index, m_componentManager);
    // }

    // clear tile structure and re-add.
    m_tileStructure.clear();
    for (std::size_t entity = 0; entity < m_positions.data.size(); ++entity) {
        m_tileStructure.addEntity(entity,
                                  m_positions.data[entity].x, m_positions.data[entity].y,
                                  m_sizes.data[entity].x, m_sizes.data[entity].y);
    }

    // get entities in range
    m_entitiesInRange.clear();
    m_tileStructure.search(m_range.x, m_range.y, m_range.width, m_range.height, m_entitiesInRange);

    moveEntities(m_positions, m_velocities, dt);
    bounceOnEdge(m_positions, m_sizes, m_velocities, m_tileStructure.currentMaxWidth(), m_tileStructure.currentMaxHeight());
}

void EcsTestState::setRange() {
    // range based on camera view
    Vector2 cameraPos = m_camera.target;
    Vector2 size = {GetScreenWidth() / m_camera.zoom, GetScreenHeight() / m_camera.zoom};
    m_range.x = cameraPos.x;
    m_range.y = cameraPos.y;
    m_range.width = size.x;
    m_range.height = size.y;
}

void EcsTestState::render() const {

    BeginMode2D(m_camera);

    // m_tileStructure.debugRender();

    for (const int entityID : m_entitiesInRange) {
        EntityType type = m_entityManager.entities[entityID];
        int posIndex = getIndex(m_positions, entityID);
        const Texture2D *texture;
        Color c;
        switch (type) {
        case EntityType::BLOB:
            texture = &m_blobTexture;
            c = RED;
            break;
        case EntityType::TREE:
            texture = &m_treeTexture;
            c = DARKBROWN;
            break;
        default:
            break;
        }

        DrawTextureEx(*texture, m_positions.data[posIndex], 1.f, 1.f, c);
    }

    EndMode2D();

    renderUi();
}

void EcsTestState::renderUi() const {
    const float x = 30.f;

    const float yOffset = 30.f;
    float y = 30.f;
    int fontSize = 20;

    std::string fpsText = "Fps: " + std::to_string(GetFPS());
    DrawText(fpsText.c_str(), x, y, fontSize, RAYWHITE);

    y += yOffset;
    std::string totalEntitiesText = "Entities: " + std::to_string(m_entityManager.entities.size());
    DrawText(totalEntitiesText.c_str(), x, y, fontSize, RAYWHITE);

    y += yOffset;
    std::string entitiesInRangeText = "Entities in range: " + std::to_string(m_entitiesInRange.size());
    DrawText(entitiesInRangeText.c_str(), x, y, fontSize, RAYWHITE);
}
