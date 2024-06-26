#ifndef IDLE_MINER_ISOMETRIC_TEST_STATE_H
#define IDLE_MINER_ISOMETRIC_TEST_STATE_H

#include "GameOptions.h"
#include "GameState.h"
#include "raylib.h"

class IsometricTestState : public GameState {
  public:
    IsometricTestState(const GameOptions &gameOptions);
    virtual ~IsometricTestState() override;
    virtual void handleInput() override;
    virtual void update(float dt) override;
    virtual void render() const override;

  private:
    const GameOptions &m_gameOptions;
};

#endif
