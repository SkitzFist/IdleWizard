#ifndef IDLE_MINER_QUAD_TREE_TEST_STATE_H
#define IDLE_MINER_QUAD_TREE_TEST_STATE_H

#include "raylib.h"

#include "CameraInput.hpp"
#include "GameState.h"
#include "QuadTreeVisualizer.h"

class QuadTreeTestState : public GameState {
  public:
    QuadTreeTestState();
    virtual ~QuadTreeTestState() override;
    virtual void handleInput() override;
    virtual void update(float dt) override;
    virtual void render() const override;

  private:
    Camera2D m_camera;
    CameraInput m_cameraInput;

    QuadTreeVisualizer m_quadTreeVisualizer;
};

#endif