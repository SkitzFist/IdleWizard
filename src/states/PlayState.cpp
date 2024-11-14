#include "PlayState.h"

#include <string>
#include <thread>

#include "Timer.h"

// update systems
#include "MoveSystem.h"
#include "WorldToRealPosSystem.h"

// render systems
#include "RenderBlobSystem.h"
#include "RenderManaAltar.h"

// UI Systems
#include "DebugEntityTypeMap.h"
#include "DebugHighlightEntitySystem.h"
#include "SystemMonitorUi.h"

// entity factories
#include "ManaAltar.h"

// data
#include "Resource.h"
#include "Vector2i.h"

inline Timer t1;
inline Timer t2;

inline int numEntities = 1000;

/*
    Todo Blood mana -> comes from sacrificing minions
*/

PlayState::PlayState(const GameOptions& gameOptions) : m_gameOptions(gameOptions),
                                                       m_ecs(),
                                                       m_components(m_ecs.components),
                                                       m_systems(m_ecs.systems),
                                                       m_worlds(createWorlds(1, 1, gameOptions.SCREEN_WIDTH, gameOptions.SCREEN_HEIGHT)) {
    m_camera.offset = {0.f, 0.f};
    m_camera.target = {0.f, 0.f};
    m_camera.rotation = 0.f;
    m_camera.zoom = 1.f;

    registerComponents();
    registerSystems();

    for (int i = 0; i < numEntities; ++i) {
        if (i < 2) {
            createManaAltar(m_ecs, m_worlds);
        } else {
            int entityId = m_ecs.createEntity(EntityType::BLOB);

            Vector2 worldPos = {GetRandomValue(10, 90) / 100.f, GetRandomValue(10, 90) / 100.f};
            m_ecs.addComponent(i, ComponentType::WORLD_POSITION, &worldPos);

            int worldIndex = 0;
            m_ecs.addComponent(i, ComponentType::WORLD_INDEX, &worldIndex);

            Vector2 pos = {0.f, 0.f};
            m_ecs.addComponent(i, ComponentType::POSITION, &pos);

            Vector2 vel = {100.f, 0.f};
            // m_ecs.addComponent(i, ComponentType::VELOCITY, &vel);

            Vector2 s = {32.f * 3.f, 32.f * 3.f};
            m_ecs.addComponent(i, ComponentType::SIZE, &s);
        }
    }
}

void PlayState::registerComponents() {
    m_components.registerComponent(ComponentType::POSITION, sizeof(Vector2), numEntities);
    m_components.registerComponent(ComponentType::WORLD_POSITION, sizeof(Vector2), numEntities);
    m_components.registerComponent(ComponentType::WORLD_INDEX, sizeof(int), numEntities);
    m_components.registerComponent(ComponentType::VELOCITY, sizeof(Vector2), numEntities);
    m_components.registerComponent(ComponentType::SIZE, sizeof(Vector2), numEntities);
    m_components.registerComponent(ComponentType::COLOR, sizeof(Color), numEntities);
    m_components.registerComponent(ComponentType::RESOURCE, sizeof(Resource), numEntities);
}

void PlayState::registerSystems() {
    // update

    m_systems.updateSystems.add<WorldToRealPosSystem>(UpdateSystemType::WORLD_TO_REAL_POS,
                                                      m_worlds,
                                                      m_components[ComponentType::POSITION],
                                                      m_components[ComponentType::WORLD_POSITION],
                                                      m_components[ComponentType::WORLD_INDEX],
                                                      m_components[ComponentType::SIZE]);

    m_systems.updateSystems.add<MoveSystem>(UpdateSystemType::VELOCITY_MOVE,
                                            m_components[ComponentType::POSITION],
                                            m_components[ComponentType::VELOCITY],
                                            m_components[ComponentType::SIZE]);

    // render
    m_systems.renderSystems.add<RenderBlobSystem>(RenderSystemType::BLOB,
                                                  m_ecs.entityTypeMap[EntityType::BLOB],
                                                  m_components[ComponentType::POSITION],
                                                  m_components[ComponentType::SIZE],
                                                  m_ecs.entityTypeMap);

    m_systems.renderSystems.add<RenderManaAltar>(RenderSystemType::MANA_ALTAR,
                                                 m_components[ComponentType::POSITION],
                                                 m_components[ComponentType::SIZE],
                                                 m_components[ComponentType::COLOR],
                                                 m_components[ComponentType::RESOURCE],
                                                 m_ecs.entityTypeMap[EntityType::MANA_ALTAR]);

    // Ui Systems
    m_systems.uiSystems.add<DebugEntityTypeMap>(UiSystemType::DEBUG_ENTITY_TYPE_MAP, m_ecs);
    m_systems.uiSystems.add<DebugHighlightEntitySystem>(UiSystemType::DEBUG_HIGHLIGHT_ENTITY_COMPONENTS, m_ecs, m_camera);
    m_systems.uiSystems.add<SystemMonitorUi>(UiSystemType::SYSTEM_MONITOR_UI, m_gameOptions, m_systems);
}

PlayState::~PlayState() {
}

bool shouldFreeze = false;

void PlayState::handleInput() {
    if (IsKeyPressed(KEY_SPACE) && m_ecs.size > 0) {
        const int randomIndex = GetRandomValue(0, m_ecs.entityTypes.size() - 1);
        m_ecs.removeEntity(randomIndex);
    }

    if (IsKeyPressed(KEY_LEFT_CONTROL)) {
        shouldFreeze = !shouldFreeze;
    }

    if (IsKeyPressed(KEY_S)) {
        split(m_worlds, m_ecs);
    }

    if (IsKeyPressed(KEY_D)) {
        grow(m_worlds, m_ecs);
    }

    // todo add pre-frame & post-frame methods to state
    ++m_systems.frameCounter;
    if (m_systems.frameCounter == m_systems.framesBeforeLog) {
        m_systems.printMeasures();
    }
}

void PlayState::update(float dt) {

    m_systems.updateUiSystems(dt);

    if (shouldFreeze) {
        return;
    }

    if (t1.getDuration() > 500.0) {
        for (int i = 0; i < m_components[ComponentType::RESOURCE].getSize(); ++i) {
            Vector2i& resource = m_components[ComponentType::RESOURCE].get<Vector2i>(i);
            resource.x += 1;

            if (resource.x > resource.y) {
                resource.x = 0;
            }
        }
        t1.begin();
    }

    m_systems.runUpdateSystems(dt);

    transition(m_worlds);
}

void PlayState::render() const {
    BeginMode2D(m_camera);

    Rectangle worldRect = {0.f, 0.f, m_worlds.width, m_worlds.height};
    for (size_t i = 0; i < m_worlds.positions.size(); ++i) {
        worldRect.x = m_worlds.positions[i].x;
        worldRect.y = m_worlds.positions[i].y;
        DrawRectangleLinesEx(worldRect, 2.f, BLUE);
    }

    m_systems.runRenderSystems();

    EndMode2D();

    drawUi();

    m_systems.renderUiSystems();
}

void PlayState::drawUi() const {
    const float x = 30.f;

    const float yOffset = 30.f;
    float y = 30.f;
    int fontSize = 20;

    DrawText(std::to_string(GetFPS()).c_str(), x, y, fontSize, RAYWHITE);
}
