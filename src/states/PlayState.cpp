#include "PlayState.h"

#include "ComponentUtils.h"
#include "BlobFactory.h"

PlayState::PlayState(const GameOptions &gameOptions) : m_gameOptions(gameOptions),
                                                       m_spatialStructure(gameOptions.SCREEN_WIDTH,
                                                                       gameOptions.SCREEN_HEIGHT,
                                                                       1, // columns
                                                                       1/*Rows*/) {
    m_camera.offset = {0.f, 0.f};
    m_camera.target = {0.f, 0.f};
    m_camera.rotation = 0.f;
    m_camera.zoom = 1.f;

    registerComponents();

    for(int i = 0; i  < 100000; ++i){
        float randX = (float)(GetRandomValue(0, m_gameOptions.SCREEN_WIDTH));
        float randY = (float)(GetRandomValue(0, m_gameOptions.SCREEN_HEIGHT));
        createBlobAt(m_entityManager,
                     m_componentManager,
                     randX, randY);
    }
}

void PlayState::registerComponents(){
    m_componentManager.registerComponent(ComponentType::POSITION, sizeof(Vector2));
    m_componentManager.registerComponent(ComponentType::SIZE, sizeof(Vector2));
    m_componentManager.registerComponent(ComponentType::VELOCITY, sizeof(Vector2));
}

PlayState::~PlayState() {
}

void PlayState::handleInput() {
}

void PlayState::update(float dt) {
    rebuildSpatialStructure();
}

void PlayState::rebuildSpatialStructure(){
    clear(m_spatialStructure);
    Component &positions = m_componentManager.components[ComponentType::POSITION];
    Component &sizes = m_componentManager.components[ComponentType::SIZE];
    Vector2 pos;
    Vector2 size;
    for (int i = 0; i < m_entityManager.entities.size(); ++i) {
        pos = readData<Vector2>(positions, getIndex(positions, i));
        size = readData<Vector2>(sizes, getIndex(sizes, i));

        addToStructure(m_spatialStructure, i, pos.x, pos.y, size.x, size.y);
    }

    sortAllElementsByWorldIndex(m_spatialStructure);
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

    y += yOffset;
    std::string totalEntitiesText = "Entities: " + std::to_string(m_entityManager.entities.size());
    DrawText(totalEntitiesText.c_str(), x, y, fontSize, RAYWHITE);
    
    // y += yOffset;
    // std::string entitiesInRangeText = "Entities in range: " + std::to_string(m_entitiesInRange.size());
    // DrawText(entitiesInRangeText.c_str(), x, y, fontSize, RAYWHITE);
}
