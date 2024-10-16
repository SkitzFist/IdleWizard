#include "PlayState.h"

#include <string>
#include <thread>

#include "Timer.h"

//update systems
#include "MoveSystem.h"

//render systems
#include "RenderBlobSystem.h"
#include "RenderManaAltar.h"

//entity factories
#include "ManaAltar.h"

//data
#include "Vector2i.h"

inline Timer t1;
inline Timer t2;

inline int numEntities = 10;

PlayState::PlayState(const GameOptions &gameOptions) : m_gameOptions(gameOptions),
                                                       m_tileMap(gameOptions.SCREEN_WIDTH, gameOptions.SCREEN_HEIGHT, numEntities),
                                                       m_ecs(),
                                                       m_components(m_ecs.components),
                                                       m_systems(m_ecs.systems){
    m_camera.offset = {0.f, 0.f};
    m_camera.target = {0.f, 0.f};
    m_camera.rotation = 0.f;
    m_camera.zoom = 1.f;

    registerComponents();
    registerSystems();

    for(int i = 0; i < numEntities - 1; ++i){
        m_ecs.createEntity(EntityType::BLOB);
        float randX = (float)GetRandomValue(0, (gameOptions.SCREEN_WIDTH * COLUMNS) - 10.f);
        float randY = (float)GetRandomValue(0, (gameOptions.SCREEN_HEIGHT * ROWS) - 10.f);
        Vector2 pos = {randX, randY};
        m_ecs.addComponent(i, ComponentType::POSITION, &pos);
        
        Vector2 vel = {100.f, 0.f};
        m_ecs.addComponent(i, ComponentType::VELOCITY, &vel);

        Vector2 s = {10.f, 10.f};
        m_ecs.addComponent(i, ComponentType::SIZE, &s);
    }

    createManaAltar(m_ecs, m_gameOptions.SCREEN_WIDTH, m_gameOptions.SCREEN_HEIGHT);
}

void PlayState::registerComponents(){
    m_components.registerComponent(ComponentType::POSITION, sizeof(Vector2), numEntities);
    m_components.registerComponent(ComponentType::VELOCITY, sizeof(Vector2), numEntities);
    m_components.registerComponent(ComponentType::SIZE, sizeof(Vector2), numEntities);
    m_components.registerComponent(ComponentType::COLOR, sizeof(Color), numEntities);
    m_components.registerComponent(ComponentType::RESOURCE, sizeof(Vector2i), numEntities);
}

void PlayState::registerSystems(){
    //update
    m_systems.registerUpdateSystem<MoveSystem>(UpdateSystemType::VELOCITY_MOVE,
                                               m_components[ComponentType::POSITION], 
                                               m_components[ComponentType::VELOCITY], 
                                               m_components[ComponentType::SIZE], 
                                               m_tileMap);

    //render
    m_systems.registerRenderSystem<RenderBlobSystem>(RenderSystemType::BLOB,
                                                     m_ecs.entityTypeMap[EntityType::BLOB],
                                                     m_components[ComponentType::POSITION],
                                                     m_components[ComponentType::SIZE],
                                                     m_ecs.entityTypeMap);
    
    m_systems.registerRenderSystem<RenderManaAltar>(RenderSystemType::MANA_ALTAR,
                                                    m_components[ComponentType::POSITION],
                                                    m_components[ComponentType::SIZE],
                                                    m_components[ComponentType::COLOR],
                                                    m_components[ComponentType::RESOURCE],
                                                    m_ecs.entityTypeMap[EntityType::MANA_ALTAR]);


}

PlayState::~PlayState() {
}

void PlayState::handleInput() {
    if(IsKeyPressed(KEY_SPACE) && m_ecs.size > 0){
        const int randomIndex = GetRandomValue(0, m_ecs.entityTypes.size() - 1);
        std::cout << "\n Removing id: " << randomIndex << "\n";
        m_ecs.removeEntity(randomIndex);
    }

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        int entityId = m_ecs.createEntity(EntityType::BLOB);
        Vector2 pos = GetScreenToWorld2D(GetMousePosition(), m_camera);
        m_components[ComponentType::POSITION].add(&pos, entityId);
        Vector2 s = {10.f, 10.f};
        m_components[ComponentType::SIZE].add(&s, entityId);
    }
}

void PlayState::update(float dt) {

    if(m_tileMap.entities.size() != m_ecs.size){
        m_tileMap.setEntitiesSize(numEntities);
    }
    
    if(t1.getDuration() > 500.0){
        for (int i = 0; i < m_components[ComponentType::RESOURCE].getSize(); ++i) {
            Vector2i &resource = m_components[ComponentType::RESOURCE].get<Vector2i>(i);
            resource.x += 1;

            if(resource.x > resource.y){
                resource.x = 0;
            }
        }
        t1.begin();
    }

    m_systems.runUpdateSystems(dt);
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

    m_systems.runRenderSystems();

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
