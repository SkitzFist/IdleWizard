#include "Game.h"
#include "IsometricTestState.h"

Game::Game(const GameOptions &gameOptions) : m_gameOptions(gameOptions) {

    InitWindow(m_gameOptions.SCREEN_WIDTH, m_gameOptions.SCREEN_HEIGHT, "Idle Miner");
    m_currentState = std::make_unique<IsometricTestState>(gameOptions);
}

Game::~Game() {
    CloseWindow();
}

void Game::run() {
    while (!WindowShouldClose()) {
        gameLoop();
    }
}

bool Game::webRun() {
    gameLoop();
    return !WindowShouldClose();
}

void Game::gameLoop() {
    handleInput();
    update();
    render();
}

void Game::handleInput() {
    m_currentState->handleInput();
}

void Game::update() {
    float dt = GetFrameTime(); // todo make proper dt calcs
    m_currentState->update(dt);
}

void Game::render() const {
    BeginDrawing();
    ClearBackground(BLACK);
    m_currentState->render();
    EndDrawing();
}
