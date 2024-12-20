#ifndef IDLE_WIZARD_PLAY_STATE_H
#define IDLE_WIZARD_PLAY_STATE_H

#include "raylib.h"

#include "GameOptions.h"
#include "GameState.h"

#include "Worlds.h"

#include "Components.h"
#include "EcsManager.h"
#include "Systems.h"

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

    EcsManager m_ecs;
    Components& m_components;
    Systems& m_systems;

    Worlds m_worlds;

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
