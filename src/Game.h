#ifndef IDLE_MINER_GAME_H_
#define IDLE_MINER_GAME_H_

#include <memory>

#include "GameOptions.h"
#include "GameState.h"
#include "raylib.h"

class Game {
  public:
    Game(const GameOptions &gameOptions);
    ~Game();

    void run();
    bool webRun();

  private:
    const GameOptions &m_gameOptions;
    std::unique_ptr<GameState> m_currentState;
    void gameLoop();
    void handleInput();
    void update();
    void render() const;
};

#endif