#include "Game.h"

#include "PlayState.h"

// test states
#include "EcsTestState.h"
#include "EntityTestState.h"
#include "IsometricTestState.h"
#include "TileStructureTestState.h"

// deug
#include <iostream>
#include <string>

Game::Game(const GameOptions &gameOptions) : m_gameOptions(gameOptions) {
    SetTraceLogLevel(LOG_NONE);
    InitWindow(m_gameOptions.SCREEN_WIDTH, m_gameOptions.SCREEN_HEIGHT, "Idle Miner");

    switchState(State::ECS_TEST);
}

Game::~Game() {
    CloseWindow();
}

void Game::switchState(State state) {
    switch (state) {
    case State::PLAY_STATE:
        m_currentState = std::make_unique<PlayState>(m_gameOptions);
        break;
    case State::ENTITY_TEST:
        m_currentState = std::make_unique<EntityTestState>();
        break;
    case State::ISOMETRIC_TEST:
        m_currentState = std::make_unique<IsometricTestState>(m_gameOptions);
        break;
    case State::TILE_STRUCTURE_TEST:
        m_currentState = std::make_unique<TileStructureTestState>(m_gameOptions);
        break;
    case State::ECS_TEST:
        m_currentState = std::make_unique<EcsTestState>(m_gameOptions);
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
    return !WindowShouldClose();
}

void Game::gameLoop() {
    try {
        handleInput();
        if (IsKeyPressed(KEY_Q)) {
            switchState(State::ECS_TEST);
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
        const float x = 30.f;

        const float yOffset = 30.f;
        float y = 30.f;
        int fontSize = 20;

        std::string fpsText = "Fps: " + std::to_string(GetFPS());
        DrawText(fpsText.c_str(), x, y, fontSize, RAYWHITE);
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
    ClearBackground(BLACK);
    m_currentState->render();
    EndDrawing();
}