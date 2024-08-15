#include "PlayState.h"

PlayState::PlayState(const GameOptions &gameOptions) : m_gameOptions(gameOptions),
                                                       m_tileStructure(gameOptions.SCREEN_WIDTH,
                                                                       gameOptions.SCREEN_HEIGHT,
                                                                       1, // columns
                                                                       2 /*Rows*/) {
    m_camera.offset = {0.f, 0.f};
    m_camera.target = {0.f, 0.f};
    m_camera.rotation = 0.f;
    m_camera.zoom = 1.f;
}

PlayState::~PlayState() {
}

void PlayState::handleInput() {
}

void PlayState::update(float dt) {
    // todo check if world should grow, if so grow

    m_tileStructure.clear();
    // todo re-add entities
}

void PlayState::render() const {
    BeginMode2D(m_camera);

    m_tileStructure.debugRender();

    EndMode2D();

    drawUi();
}

void PlayState::drawUi() const {
}
