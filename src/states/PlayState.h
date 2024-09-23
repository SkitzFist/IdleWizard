#ifndef IDLE_WIZARD_PLAY_STATE_H
#define IDLE_WIZARD_PLAY_STATE_H

#include "raylib.h"

#include "GameOptions.h"
#include "GameState.h"

#include "TileMap.h"

#include "ComponentManager.h"
#include "Component.h"

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

    Components m_components;

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
