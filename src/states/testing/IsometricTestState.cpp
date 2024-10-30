#include "IsometricTestState.h"
#include <iostream>
#include <string>

IsometricTestState::IsometricTestState(const GameOptions& gameOptions) : m_gameOptions(gameOptions),
                                                                         m_camera{{0.f, 0.f}, {0.f, 0.f}, 0.f, 1.f} {
}

IsometricTestState::~IsometricTestState() {
}

void IsometricTestState::handleInput() {
    static int cameraSpeed = 2;
    if (IsKeyDown(KEY_W)) {
        m_camera.target.y -= cameraSpeed;
    } else if (IsKeyDown(KEY_S)) {
        m_camera.target.y += cameraSpeed;
    }

    if (IsKeyDown(KEY_A)) {
        m_camera.target.x -= cameraSpeed;
    } else if (IsKeyDown(KEY_D)) {
        m_camera.target.x += cameraSpeed;
    }

    if (IsKeyPressed(KEY_ONE)) {
        cameraSpeed *= 2;
    } else if (IsKeyPressed(KEY_TWO)) {
        cameraSpeed /= 2;
    }
}

void IsometricTestState::update(float dt) {
}

void IsometricTestState::render() const {
    BeginMode2D(m_camera);
    drawNormalGrid();
    drawIsoGrid();
    EndMode2D();
}

void IsometricTestState::drawNormalGrid() const {
    for (int y = 0; y < Isometric::NUM_TILES_Y; ++y) {
        for (int x = 0; x < Isometric::NUM_TILES_X; ++x) {
            const int width = Isometric::TILE_WIDTH;
            const int height = Isometric::TILE_HEIGHT;
            Vector2 tl = {Isometric::ORIGIN.x + x * width, Isometric::ORIGIN.y + y * height};
            Vector2 tr = {tl.x + width, tl.y};
            Vector2 bl = {tl.x, tl.y + height};
            Vector2 br = {bl.x + width, bl.y};
            drawRectangle({tl, tr, bl, br}, RAYWHITE);
        }
    }
}

void IsometricTestState::drawIsoGrid() const {
    for (int y = 0; y < Isometric::NUM_TILES_Y; ++y) {
        for (int x = 0; x < Isometric::NUM_TILES_X; ++x) {
            DrawCircleV(Isometric::toScreen(x, y), 5.f, RED);
            drawRectangle(Isometric::getRectangleData((float)x, (float)y), RAYWHITE);
        }
    }
}

// top-left, top-bot, top-right, top-bot
void IsometricTestState::drawRectangle(const Isometric::Rectangle& rectangleData, const Color& c) const {
    DrawLineV(rectangleData.topLeft, rectangleData.topRight, c);
    DrawLineV(rectangleData.topLeft, rectangleData.botLeft, c);
    DrawLineV(rectangleData.botRight, rectangleData.botLeft, c);
    DrawLineV(rectangleData.botRight, rectangleData.topRight, c);
}
