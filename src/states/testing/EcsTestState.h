#ifndef IDLE_MINER_ECS_TEST_STATE_H
#define IDLE_MINER_ECS_TEST_STATE_H

#include <unordered_set>

#include "raylib.h"

#include "CameraInput.hpp"
#include "GameOptions.h"
#include "GameState.h"

// spatial
#include "TileStructure.h"

// ECS
#include "ComponentManager.h"
#include "EntityManager.h"
#include "VectorComponent.h"

class EcsTestState : public GameState {
  public:
    EcsTestState(const GameOptions &gameOptions);
    virtual ~EcsTestState() override;
    virtual void handleInput() override;
    virtual void update(float dt) override;
    virtual void render() const override;

  private:
    Camera2D m_camera;
    CameraInput m_cameraInput;

    // spatial
    TileStructure m_tileStructure;
    Rectangle m_range;
    std::unordered_set<int> m_entitiesInRange;

    // Ecs
    EntityManager m_entityManager;
    ComponentManager m_componentManager;
    VectorComponent m_positions;
    VectorComponent m_sizes;
    VectorComponent m_velocities;

    // textures
    Texture2D m_blobTexture;
    Texture2D m_treeTexture;

  private:
    void registerComponents();
    void setRange();
    void renderUi() const;
};

#endif
