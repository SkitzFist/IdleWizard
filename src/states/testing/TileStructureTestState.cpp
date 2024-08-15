#include "TileStructureTestState.h"

// Debug
#include <chrono>
#include <iostream>
#include <string>

inline int initNumEntities = 100000;
inline int numEntities = 0;
inline float CIRCLE_MAX_SIZE = 50.f;

inline int rows = 1;
inline int initColumns = 500;

TileStructureTestState::TileStructureTestState(const GameOptions &gameOption) : m_gameoptions(gameOption),
                                                                                m_tileStructure(m_gameoptions.SCREEN_WIDTH,
                                                                                                m_gameoptions.SCREEN_HEIGHT,
                                                                                                rows,
                                                                                                initColumns),
                                                                                m_range({0.f, 0.f, 50.f, 50.f}) {
    // init
    m_camera.offset = {0.f, 0.f};
    m_camera.target = {0.f, 0.f};
    m_camera.rotation = 0.f;
    m_camera.zoom = 1.f;

    for (int i = 0; i < initNumEntities; ++i) {
        createEntity();
    }

    // create circle texture
    RenderTexture2D target = LoadRenderTexture(CIRCLE_MAX_SIZE, CIRCLE_MAX_SIZE);
    BeginTextureMode(target);
    ClearBackground(BLANK);
    DrawRectangle(0.f, 0.f, CIRCLE_MAX_SIZE, CIRCLE_MAX_SIZE, WHITE);
    EndTextureMode();
    m_texture = target.texture;
}

TileStructureTestState::~TileStructureTestState() {
}

void TileStructureTestState::createEntity(const float minX, const float minY) {
    float radius = static_cast<float>(GetRandomValue(4, CIRCLE_MAX_SIZE));

    float min = minX + radius;
    float max = m_tileStructure.currentMaxWidth() - radius;
    float x = static_cast<float>(GetRandomValue(min, max));

    min = minY + radius;
    max = m_tileStructure.currentMaxHeight() - radius;
    float y = static_cast<float>(GetRandomValue(min, max));

    int i = numEntities;
    m_positions.add(i, x, y);
    m_sizes.add(i, radius, radius);

    ++numEntities;
}

void TileStructureTestState::handleInput() {
    m_cameraInput.handleInput(m_camera);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), m_camera);
        m_positions.add(numEntities, mousePos.x, mousePos.y);
        m_sizes.add(numEntities, CIRCLE_MAX_SIZE, CIRCLE_MAX_SIZE);
        ++numEntities;
    }
}

inline Vector2 marker = {0.f, 0.f};

void TileStructureTestState::update(float dt) {
    // world expansion
    marker.x = m_camera.target.x + m_gameoptions.SCREEN_WIDTH / 2.f;
    if (marker.x >= m_tileStructure.currentMaxWidth()) {
        m_tileStructure.growColumns();
        float minX = m_tileStructure.prevMaxWidth();
        float minY = m_tileStructure.prevMaxHeight();
        for (int i = 0; i < initNumEntities; ++i) {
            createEntity(minX, minY);
        }
    }

    // clear and re-add entities to tile structure
    m_tileStructure.clear();
    for (int id = 0; id < numEntities; ++id) {
        m_tileStructure.addEntity(id,
                                  m_positions.data[id].x,
                                  m_positions.data[id].y,
                                  m_sizes.data[id].x,
                                  m_sizes.data[id].y);
    }

    // get entities in range
    setRange();
    m_entitiesInRange.clear();
    m_tileStructure.search(m_range.x, m_range.y, m_range.width, m_range.height, m_entitiesInRange);
}

void TileStructureTestState::setRange() {
    // range based on camera view
    Vector2 cameraPos = m_camera.target;
    Vector2 size = {GetScreenWidth() / m_camera.zoom, GetScreenHeight() / m_camera.zoom};
    m_range.x = cameraPos.x;
    m_range.y = cameraPos.y;
    m_range.width = size.x;
    m_range.height = size.y;
}

void TileStructureTestState::render() const {
    BeginMode2D(m_camera);

    // m_tileStructure.debugRender();

    // render entities
    for (const int id : m_entitiesInRange) {
        float scale = m_sizes.data[id].x / CIRCLE_MAX_SIZE;
        DrawTextureEx(
            m_texture,
            m_positions.data[id],
            0.f,
            scale,
            RED);
    }

    // draw range
    // DrawRectangleLinesEx(m_range, 2.f, YELLOW);

    EndMode2D();

    renderUi();
}

void TileStructureTestState::renderUi() const {
    const float x = 30.f;

    const float yOffset = 30.f;
    float y = 30.f;
    int fontSize = 20;

    std::string fpsText = "Fps: " + std::to_string(GetFPS());
    DrawText(fpsText.c_str(), x, y, fontSize, RAYWHITE);

    y += yOffset;
    std::string numEntitiesText = "Entities: " + std::to_string(numEntities);
    DrawText(numEntitiesText.c_str(), x, y, fontSize, RAYWHITE);

    y += yOffset;
    std::string numEntitiesInRangeText = "In Range: " + std::to_string(m_entitiesInRange.size());
    DrawText(numEntitiesInRangeText.c_str(), x, y, fontSize, RAYWHITE);
}
