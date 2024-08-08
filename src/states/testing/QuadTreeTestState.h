#ifndef IDLE_MINER_QUAD_TREE_TEST_STATE_H
#define IDLE_MINER_QUAD_TREE_TEST_STATE_H

#include "raylib.h"

#include "CameraInput.hpp"
#include "GameState.h"
#include "TiledDataOrientedQuadTree.h"

// components
#include "Positions.h"
#include "Sizes.h"
#include "Velocities.h"

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

    // spatial hashing
    TiledDataOrientedQuadTree m_quadTree;

    // components
    Positions m_positions;
    Sizes m_sizes;
    Velocities m_velocities;

    // texture
    Texture2D m_circleTexture;

  private:
    void createEntity();

    void drawUi() const;
};

#endif