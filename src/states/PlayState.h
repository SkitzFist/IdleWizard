#ifndef IDLE_MINER_PLAY_STATE_H
#define IDLE_MINER_PLAY_STATE_H

#include "raylib.h"

#include "GameOptions.h"
#include "GameState.h"
#include "TileStructure.h"

// components
#include "VectorComponent.h"

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
    TileStructure m_tileStructure;

    // ECS
    VectorComponent m_positions;
    VectorComponent m_sizes;

  private:
    void drawUi() const;
};

#endif
