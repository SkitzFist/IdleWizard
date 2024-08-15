#ifndef IDLE_MINER_TILE_STRUCTURE_TEST_STATE_H
#define IDLE_MINER_TILE_STRUCTURE_TEST_STATE_H

#include <unordered_set>

#include "raylib.h"

#include "CameraInput.hpp"
#include "GameOptions.h"
#include "GameState.h"
#include "TileStructure.h"

// components
#include "VectorComponent.h"

class TileStructureTestState : public GameState {
  public:
    TileStructureTestState(const GameOptions &gameOptions);
    virtual ~TileStructureTestState() override;
    virtual void handleInput() override;
    virtual void update(float dt) override;
    virtual void render() const override;

  private:
    const GameOptions &m_gameoptions;

    Camera2D m_camera;
    TileStructure m_tileStructure;

    CameraInput m_cameraInput;

    // components
    VectorComponent m_positions;
    VectorComponent m_sizes;

    // range
    Rectangle m_range;
    std::unordered_set<int> m_entitiesInRange;

    // textures
    Texture2D m_texture;

  private:
    void createEntity(const float minX = 0.f, const float minY = 0.f);
    void setRange();
    void renderUi() const;
};

#endif
