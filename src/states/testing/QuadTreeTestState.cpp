#include "QuadTreeTestState.h"

QuadTreeTestState::QuadTreeTestState() : m_camera(), m_quadTreeVisualizer(8) {
    m_camera.offset = {0, 0};
    m_camera.target = {0, 0};
    m_camera.rotation = 0.f;
    m_camera.zoom = 1.f;
}

QuadTreeTestState::~QuadTreeTestState() {
}

void QuadTreeTestState::handleInput() {
    m_cameraInput.handleInput(m_camera);
}

void QuadTreeTestState::update(float dt) {
}

void QuadTreeTestState::render() const {
    BeginMode2D(m_camera);
    m_quadTreeVisualizer.render();
    EndMode2D();
}
