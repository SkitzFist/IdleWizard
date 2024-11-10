#include "Game.h"

#include "PlayState.h"

// test states
#include "IsometricTestState.h"

// deug
#include <iostream>
#include <string>

inline constexpr const Game::State initState = Game::State::PLAY_STATE;

Game::Game(const GameOptions& gameOptions) : m_gameOptions(gameOptions) {
    // SetTraceLogLevel(LOG_NONE);
    InitWindow(m_gameOptions.SCREEN_WIDTH, m_gameOptions.SCREEN_HEIGHT, "Idle Wizard");
    // ToggleFullscreen();
    switchState(initState);
}

Game::~Game() {
}

void Game::switchState(State state) {
    switch (state) {
    case State::PLAY_STATE:
        m_currentState = std::make_unique<PlayState>(m_gameOptions);
        break;
        break;
    case State::ISOMETRIC_TEST:
        m_currentState = std::make_unique<IsometricTestState>(m_gameOptions);
        break;
    default:
        break;
    }
}

void Game::run() {
    while (!WindowShouldClose()) {
        gameLoop();
    }
}

bool Game::webRun() {
    gameLoop();
    return true;
}

void Game::gameLoop() {
    try {
        handleInput();
        if (IsKeyPressed(KEY_Q)) {
            switchState(initState);
        }
    } catch (...) {
        std::cout << "Error in handleInput\n";
    }
    try {
        update();
    } catch (...) {
        std::cerr << "error in update\n";
    }

    try {
        render();
    } catch (...) {
        std::cerr << "Error in render\n";
    }
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
    ClearBackground(DARKGRAY);
    m_currentState->render();
    EndDrawing();
}