#include "PlayState.h"

#include <string>
#include <thread>

#include "Timer.h"

inline Timer t1;
inline Timer t2;

inline int numEntities = 1000;

struct Transformator{
    float x, y, width, height;
};

PlayState::PlayState(const GameOptions &gameOptions) : m_gameOptions(gameOptions),
                                                       m_tileMap(gameOptions.SCREEN_WIDTH, gameOptions.SCREEN_HEIGHT, numEntities){
    m_camera.offset = {0.f, 0.f};
    m_camera.target = {0.f, 0.f};
    m_camera.rotation = 0.f;
    m_camera.zoom = 1.f;

    registerComponents();

    const float size = 10.f;
    for(int i = 0; i < numEntities; ++i){
        float randX = (float)GetRandomValue(0, (gameOptions.SCREEN_WIDTH * COLUMNS) - size);
        float randY = (float)GetRandomValue(0, (gameOptions.SCREEN_HEIGHT * ROWS) - size);
        Vector2 pos = {randX, randY};
        m_components[ComponentType::POSITION].add(&pos);
        Vector2 s = {size, size};
        m_components[ComponentType::SIZE].add(&s);
    }
}

void PlayState::registerComponents(){
    m_components.registerComponent(ComponentType::POSITION, sizeof(Vector2), numEntities);
    m_components.registerComponent(ComponentType::SIZE, sizeof(Vector2), numEntities);
}

PlayState::~PlayState() {
}

void PlayState::handleInput() {
}

void PlayState::update(float dt) {

   //t1.begin();
        rebuildTileMapEntity();
   //std::cout << "Rebuilding tileMap took " << t1.getDuration() << "ms\n";

    //move Entities
    Component &positions = m_components[ComponentType::POSITION];
    
    for (int i = 0; i < numEntities; ++i) {
        Vector2& vec = positions.get<Vector2>(i);
        vec.x += 100.f * dt;
        m_tileMap.entities[i] = (static_cast<int>(vec.y) / m_tileMap.tileHeight) * COLUMNS + (static_cast<int>(vec.x) / m_tileMap.tileWidth) % (COLUMNS * ROWS);
    }

    for(int i = 0; i < numEntities; ++i){
        Vector2& vec = positions.get<Vector2>(i);

        if(vec.x >= m_gameOptions.SCREEN_WIDTH * COLUMNS){
            vec.x = 0.f;
        }
    }
}

void PlayState::rebuildTileMap() {
    Component &positions = m_components[ComponentType::POSITION];
    Component &sizes = m_components[ComponentType::SIZE];

    m_tileMap.clear();
    Vector2 pos;
    Vector2 size;
    for (int i = 0; i < numEntities; ++i) {
        pos = positions.get<Vector2>(i);
        size = sizes.get<Vector2>(i);
        m_tileMap.add(i,
                      pos.x, pos.y,
                      size.x, size.y);
    }    
}

void PlayState::rebuildTileMapEntity() {
    m_tileMap.clear();
    m_tileMap.entityAdd();
}

void PlayState::render() const {
    BeginMode2D(m_camera);

    const Component& positions = m_components[ComponentType::POSITION];
    const Component& sizes = m_components[ComponentType::SIZE];
    Vector2 pos;
    Vector2 size;
    for(int i = 0; i < numEntities; ++i){
        pos = positions.get<Vector2>(i);
        size = sizes.get<Vector2>(i);
        DrawCircle(pos.x, pos.y, size.x, RED);
    }

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
