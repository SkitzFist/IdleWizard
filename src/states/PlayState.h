#ifndef IDLE_WIZARD_PLAY_STATE_H
#define IDLE_WIZARD_PLAY_STATE_H

#include "raylib.h"

#include "GameOptions.h"
#include "GameState.h"

#include "TileMap.h"

#include "Components.h"
#include "EcsManager.h"
#include "Systems.h"

// debug
#include "DebugEntityTypeMap.h"
#include "DebugHighlightEntitySystem.h"

class PlayState : public GameState {
  public:
    PlayState(const GameOptions& GameOptions);
    virtual ~PlayState() override;
    virtual void handleInput() override;
    virtual void update(float dt) override;
    virtual void render() const override;

  private:
    const GameOptions& m_gameOptions;
    Camera2D m_camera;

    TileMap m_tileMap;

    EcsManager m_ecs;
    Components& m_components;
    Systems& m_systems;

    // tmp textures;
    Texture2D m_texture;

    // debug
    DebugHighlightEntitySystem m_debugHighlight;
    DebugEntityTypeMap m_debugEntityTypeMap;

  private:
    // init
    void registerComponents();
    void registerSystems();

    // input

    // update
    void rebuildTileMap();
    void rebuildTileMapEntity();

    // render
    void drawUi() const;
};

#endif
