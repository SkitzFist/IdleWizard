#include "PlayState.h"

#include <string>

#include "Timer.h"

inline constexpr const int numEntities = 10000;
PlayState::PlayState(const GameOptions &gameOptions) : m_gameOptions(gameOptions){
    m_camera.offset = {0.f, 0.f};
    m_camera.target = {0.f, 0.f};
    m_camera.rotation = 0.f;
    m_camera.zoom = 1.f;

    registerComponents();

    for(int i = 0; i  < numEntities; ++i){
    }
}

void PlayState::registerComponents(){
}

PlayState::~PlayState() {
}

void PlayState::handleInput() {
}

void PlayState::update(float dt) {
    rebuildSpatialStructure();
}

void PlayState::rebuildSpatialStructure(){
}

void PlayState::render() const {
    BeginMode2D(m_camera);

    EndMode2D();

    drawUi();
}

void PlayState::drawUi() const {
    const float x = 30.f;

    const float yOffset = 30.f;
    float y = 30.f;
    int fontSize = 20;

    std::string fpsText = "Fps: " + std::to_string(GetFPS());
    DrawText(fpsText.c_str(), x, y, fontSize, RAYWHITE);

    // y += yOffset;
    // std::string totalEntitiesText = "Entities: " + std::to_string(m_entityManager.entities.size());
    // DrawText(totalEntitiesText.c_str(), x, y, fontSize, RAYWHITE);
    
    // y += yOffset;
    // std::string entitiesInRangeText = "Entities in range: " + std::to_string(m_entitiesInRange.size());
    // DrawText(entitiesInRangeText.c_str(), x, y, fontSize, RAYWHITE);
}
