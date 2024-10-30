#include "DebugEntityTypeMap.h"

#include <string>

DebugEntityTypeMap::DebugEntityTypeMap(EcsManager& ecs) : m_ecs(ecs), m_enabled(true) {
}

void DebugEntityTypeMap::update(float dt) {
    if (IsKeyPressed(KEY_ONE)) {
        m_enabled = !m_enabled;
    }
}

void DebugEntityTypeMap::render() const {
    if (!m_enabled) {
        return;
    }

    // draw container
    Vector2 containerSize = {GetScreenWidth() * 0.2f, GetScreenHeight() * 0.8f};
    Vector2 containerPos = {20.f, 60.f};
    Rectangle containerRect = {containerPos.x, containerPos.y, containerSize.x, containerSize.y};
    float containerThickness = 2.f;
    Color colorBase = LIGHTGRAY;
    colorBase.a = 180;
    DrawRectangle(containerPos.x, containerPos.y, containerSize.x, containerSize.y, colorBase);
    DrawRectangleLinesEx(containerRect, containerThickness, RAYWHITE);

    float initXOffset = containerPos.x + 5.f;
    float initYOffset = containerPos.y + 5.f;
    float xOffset = 80.f;
    float yOffset = 20.f;
    int fontSize = 20;
    Vector2 textPos = {initXOffset, initYOffset};

    // entity list
    for (int i = 0; i < m_ecs.size; ++i) {
        std::string str = std::to_string(i) + " | " + toString(m_ecs.entityTypes[i]);
        DrawText(str.c_str(), textPos.x, textPos.y, fontSize, BLACK);
        textPos.y += yOffset;
    }

    textPos.x += xOffset * 2.25f;
    textPos.y = initYOffset;
    // TypeMap

    for (int i = 0; i < (int)EntityType::COUNT; ++i) {
        EntityType type = (EntityType)i;
        if (type == EntityType::COUNT || type == EntityType::WIZARD) {
            continue;
        }

        std::vector<int>& entities = m_ecs.entityTypeMap[type];
        if (entities.empty())
            continue;
        std::string typeString = toString(type);
        DrawText(typeString.c_str(), textPos.x, textPos.y, fontSize, BLACK);
        textPos.y += yOffset;

        for (const int id : entities) {
            std::string idStr = std::to_string(id);
            DrawText(idStr.c_str(), textPos.x, textPos.y, fontSize, BLACK);
            textPos.y += yOffset;
        }

        textPos.x += xOffset;
        textPos.y = initYOffset;
    }
}
