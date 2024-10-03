#ifndef IDLE_WIZARD_PLAY_STATE_H
#define IDLE_WIZARD_PLAY_STATE_H

#include "raylib.h"

#include "GameOptions.h"
#include "GameState.h"

#include "TileMap.h"

#include "EcsManager.h"
#include "Components.h"

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

    TileMap m_tileMap;

    EcsManager m_ecs;
    Components& m_components;

    //tmp textures;
    Texture2D m_texture;

  private:
    //init
    void registerComponents();

    //input

    //update
    void rebuildTileMap();
    void rebuildTileMapEntity();

    //render
    void drawUi() const;
};

#endif
