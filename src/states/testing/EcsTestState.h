#ifndef IDLE_MINER_ECS_TEST_STATE_H
#define IDLE_MINER_ECS_TEST_STATE_H

#include "raylib.h"

#include "GameState.h"

// spatial
#include "TileStructure.h"

// ECS
#include "ComponentManager.h"
#include "EntityManager.h"
#include "VectorComponent.h"

class EcsTestState : public GameState {
  public:
    EcsTestState();
    virtual ~EcsTestState() override;
    virtual void handleInput() override;
    virtual void update(float dt) override;
    virtual void render() const override;

  private:
    Camera2D m_camera;

    // spatial
    TileStructure m_tileStructure;

    // Ecs
    EntityManager m_entityManager;
    ComponentManager m_componentManager;
    VectorComponent m_positions;
    VectorComponent m_sizes;
    VectorComponent m_velocities;

  private:
    void renderUi() const;
};

#endif
