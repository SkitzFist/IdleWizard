#include "DebugHighlightEntitySystem.h"

#include <string>

DebugHighlightEntitySystem::DebugHighlightEntitySystem(EcsManager &ecsManager, Camera2D &camera) : m_ecs(ecsManager),
                                                                                                   m_components(ecsManager.components),
                                                                                                   m_camera(camera) {}

void DebugHighlightEntitySystem::update(float dt) {
    m_entities.clear();
    Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), m_camera);
    std::vector<int> entitiesFound;
    for (int i = 0; i < m_ecs.size; ++i) {
        Vector2 &pos = m_components[(int)ComponentType::POSITION].getFromId<Vector2>(i);
        Vector2 &size = m_components[(int)ComponentType::SIZE].getFromId<Vector2>(i);

        if (mousePos.x > pos.x && mousePos.x < pos.x + size.x &&
            mousePos.y > pos.y && mousePos.y < pos.y + size.y) {
            if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                m_ecs.removeEntity(i);
            } else {
                m_entities.emplace_back(i);
            }
        }
    }
}

void DebugHighlightEntitySystem::render() const {
    if (m_entities.empty()) {
        return;
    }
    // draw container
    Vector2 containerSize = {GetScreenWidth() * 0.125f, GetScreenHeight() * 0.8f};
    Vector2 containerPos = {GetScreenWidth() - containerSize.x, 60.f};
    Rectangle containerRect = {containerPos.x, containerPos.y, containerSize.x, containerSize.y};
    float containerThickness = 2.f;
    Color colorBase = LIGHTGRAY;
    colorBase.a = 180;
    DrawRectangle(containerPos.x, containerPos.y, containerSize.x, containerSize.y, colorBase);
    DrawRectangleLinesEx(containerRect, containerThickness, RAYWHITE);

    float yOffset = 20.f;
    float xOffset = 5.f;
    int fontSize = 20;
    Vector2 textPos = {containerPos.x + 5.f, containerPos.y + 5.f};

    for (std::size_t i = 0; i < m_entities.size(); ++i) {
        // draw id
        int id = m_entities[i];
        std::string idStr = "Id:\t" + std::to_string(id);
        DrawText(idStr.c_str(), textPos.x, textPos.y, fontSize, BLACK);
        textPos.y += yOffset;

        // draw type
        EntityType type = m_ecs.entityTypes[id];
        std::string typeStr = "Type:\t" + toString(type);
        DrawText(typeStr.c_str(), textPos.x, textPos.y, fontSize, BLACK);
        textPos.y += yOffset;

        // components
        DrawText("Components: ", textPos.x, textPos.y, fontSize, BLACK);
        textPos.y += yOffset;
        std::string componentsString = "";
        int count = 0;
        for (int i = 0; i < (int)ComponentType::COUNT; ++i) {
            if (m_ecs.hasComponent(id, (ComponentType)i)) {
                componentsString += ("\t" + toString((ComponentType)i) + "\n");
                ++count;
            }
        }

        DrawText(componentsString.c_str(), textPos.x, textPos.y, fontSize, BLACK);
        textPos.y += (count * yOffset);

        textPos.y += yOffset * 2.f;
    }
}