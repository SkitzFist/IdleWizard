#ifndef IDLE_MINER_PLAY_STATE_H
#define IDLE_MINER_PLAY_STATE_H

#include "raylib.h"

#include "GameOptions.h"
#include "GameState.h"

#include "EntityManager.h"
#include "ComponentManager.h"
#include "TileStructure.h"

class PlayState : public GameState {
  public:
    PlayState(const GameOptions &GameOptions);
    virtual ~PlayState() override;
    virtual void handleInput() override;
    virtual void update(float dt) override;
    virtual void render() const override;

  private:
    const GameOptions &m_gameOptions;
    Camera2D m_camera;
    EntityManager m_entityManager;
    ComponentManager m_componentManager;
    TileStructure m_spatialStructure;

  private:
    //init
    void registerComponents();

    //input

    //update
    void rebuildSpatialStructure();
    //render
    void drawUi() const;
};

#endif
