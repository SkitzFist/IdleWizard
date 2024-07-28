#ifndef IDLE_MINER_ISOMETRIC_h_
#define IDLE_MINER_ISOMETRIC_h_

#include "GameOptions.h"
#include "raylib.h"

namespace Isometric {
inline constexpr const int TILE_WIDTH = 128;
inline constexpr const int TILE_HEIGHT = 64;
inline constexpr const Vector2 ORIGIN = {2000.f, 0.f};
inline constexpr const int NUM_TILES_X = 28;
inline constexpr const int NUM_TILES_Y = 20;

struct Rectangle {
    Vector2 topLeft, topRight, botLeft, botRight;
};

inline Vector2 toScreen(const Vector2 &pos) {
    return {
        (pos.x - pos.y) * (TILE_WIDTH / 2),
        (pos.x + pos.y) * (TILE_HEIGHT / 2)};
}

inline Vector2 toScreen(float x, float y) {
    return toScreen({x, y});
}

inline Rectangle getRectangleData(float x, float y) {
    const int spacing = 1;
    return {
        toScreen(x, y),
        toScreen(x + spacing, y),
        toScreen(x, y + spacing),
        toScreen(x + spacing, y + spacing)};
}

}; // namespace Isometric
#endif
