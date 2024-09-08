#include "raylib.h"

#if defined(PLATFORM_WEB)
#include "emscripten.h"
#endif

#include "Game.h"
#include "GameOptions.h"
#include "raylib.h"

// #include "tests/ECS/ComponentTesting.hpp"
#include "tests/data-structures/SpatialTest.hpp"

constexpr const int SCREEN_WIDTH = 1920;
constexpr const int SCREEN_HEIGHT = 1080;

int main() {

    spatialTest();
    return 0;

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(webLoob, 0, 1);
#else
    GameOptions gameOptions(SCREEN_WIDTH, SCREEN_HEIGHT);
    Game game(gameOptions);
    game.run();
#endif

    return 0;
}

#if defined(PLATFORM_WEB)

Game &getGameInstance() {
    static Game game({SCREEN_WIDTH, SCREEN_HEIGHT});
    return game;
}

void webLoob() {
    if (!getGameInstance().webRun()) {
        webTearDown();
    }
}

void webTearDown() {
    emscripten_cancel_main_loop();
    CloseWindow();
}

#endif
