#include "PlayState.h"

#include <string>
#include <thread>

#include "Timer.h"

inline Timer t1;
inline Timer t2;

inline int numEntities = 100;

PlayState::PlayState(const GameOptions &gameOptions) : m_gameOptions(gameOptions),
                                                       m_tileMap(gameOptions.SCREEN_WIDTH, gameOptions.SCREEN_HEIGHT, numEntities),
                                                       m_ecs(),
                                                       m_components(m_ecs.components){
    m_camera.offset = {0.f, 0.f};
    m_camera.target = {0.f, 0.f};
    m_camera.rotation = 0.f;
    m_camera.zoom = 1.f;

    registerComponents();

    const float size = 10.f;
    RenderTexture2D target = LoadRenderTexture(size, size);
    BeginTextureMode(target);
    ClearBackground(BLANK);
    DrawRectangle(0.f, 0.f, size, size, WHITE);
    EndTextureMode();
    m_texture = target.texture;

    for(int i = 0; i < numEntities; ++i){
        m_ecs.createEntity(EntityType::BLOB);
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
    if(IsKeyPressed(KEY_SPACE)){
        const int randomIndex = GetRandomValue(0, m_ecs.entityTypes.size() - 1);
        m_ecs.removeEntity(randomIndex);
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        m_ecs.createEntity(EntityType::BLOB);
        Vector2 pos = GetScreenToWorld2D(GetMousePosition(), m_camera);
        m_components[ComponentType::POSITION].add(&pos);
        Vector2 s = {10.f, 10.f};
        m_components[ComponentType::SIZE].add(&s);
    }
}

void PlayState::update(float dt) {

    if(m_tileMap.entities.size() != m_ecs.size){
        m_tileMap.setEntitiesSize(numEntities);
    }

    // move Entities
    Component &positions = m_components[ComponentType::POSITION];
    for (int i = 0; i < m_ecs.size; ++i) {
        Vector2 &vec = positions.get<Vector2>(i);
        //vec.x += 100.f * dt;
        m_tileMap.entities[i] = (static_cast<int>(vec.y) / m_tileMap.tileHeight) * COLUMNS + (static_cast<int>(vec.x) / m_tileMap.tileWidth) % (COLUMNS * ROWS);
    }

    //t1.begin();
    rebuildTileMapEntity();
    //std::cout << "Rebuilding tileMap took " << t1.getDuration() << "ms\n";

    for (int i = 0; i < m_ecs.size; ++i) {
        Vector2& vec = positions.get<Vector2>(i);
        if(vec.x >= m_gameOptions.SCREEN_WIDTH * COLUMNS){
            vec.x = -12.f;
        }
    }
}

void PlayState::rebuildTileMap() {
    Component &positions = m_components[ComponentType::POSITION];
    Component &sizes = m_components[ComponentType::SIZE];

    m_tileMap.clear();
    Vector2 pos;
    Vector2 size;
    for (int i = 0; i < m_ecs.size; ++i) {
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
    Rectangle src = {0.f, 0.f, 10.f, 10.f};
    Rectangle dst = {0.f, 0.f, 10.f, 10.f};
    Vector2 origin = {0.f, 0.f};

    for(int i = 0; i < m_ecs.size; ++i){
        pos = positions.get<Vector2>(i);
        size = sizes.get<Vector2>(i);
        dst.x = pos.x;
        dst.y = pos.y;
        dst.width = size.x;
        dst.height = size.y;
        DrawTexturePro(m_texture, src, dst, origin, 0.f, RED);
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

    y += yOffset;
    std::string totalEntitiesText = "Entities: " + std::to_string(m_ecs.size);
    DrawText(totalEntitiesText.c_str(), x, y, fontSize, RAYWHITE);
    
    // y += yOffset;
    // std::string entitiesInRangeText = "Entities in range: " + std::to_string(m_entitiesInRange.size());
    // DrawText(entitiesInRangeText.c_str(), x, y, fontSize, RAYWHITE);
}
