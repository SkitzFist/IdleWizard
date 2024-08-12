#include "Game.h"

// test states
#include "EntityTestState.h"
#include "IsometricTestState.h"
#include "QuadTreeTestState.h"
#include "TileStructureTestState.h"

// deug
#include <iostream>

Game::Game(const GameOptions &gameOptions) : m_gameOptions(gameOptions) {
    SetTraceLogLevel(LOG_NONE);
    InitWindow(m_gameOptions.SCREEN_WIDTH, m_gameOptions.SCREEN_HEIGHT, "Idle Miner");

    switchState(State::TILE_STRUCTURE_TEST);
}

Game::~Game() {
    CloseWindow();
}

void Game::switchState(State state) {
    switch (state) {
    case State::ENTITY_TEST:
        m_currentState = std::make_unique<EntityTestState>();
        break;
    case State::ISOMETRIC_TEST:
        m_currentState = std::make_unique<IsometricTestState>(m_gameOptions);
        break;
    case State::QUAD_TREE_TEST:
        m_currentState = std::make_unique<QuadTreeTestState>();
        break;
    case State::TILE_STRUCTURE_TEST:
        m_currentState = std::make_unique<TileStructureTestState>(m_gameOptions);
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
    ClearBackground(BLACK);
    m_currentState->render();
    EndDrawing();
}