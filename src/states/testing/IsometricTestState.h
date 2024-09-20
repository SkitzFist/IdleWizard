#ifndef IDLE_WIZARD_ISOMETRIC_TEST_STATE_H
#define IDLE_WIZARD_ISOMETRIC_TEST_STATE_H

#include "GameOptions.h"
#include "GameState.h"
#include "Isometric.h"
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
    Camera2D m_camera;

    void drawNormalGrid() const;
    void drawIsoGrid() const;
    void drawRectangle(const Isometric::Rectangle &rectangleData, const Color &c) const;
};

#endif
