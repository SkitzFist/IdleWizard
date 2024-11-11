#if defined(PLATFORM_WEB)
#include "emscripten.h"
#endif

#include "Game.h"
#include "GameOptions.h"
#include "raylib.h"

#include "tests/ecs/ComponentTest.h"
#include "tests/ecs/EcsManagerTest.h"

constexpr const int SCREEN_WIDTH = 1920;
constexpr const int SCREEN_HEIGHT = 1080;

#if defined(PLATFORM_WEB)

Game& getGameInstance() {
    static Game game({SCREEN_WIDTH, SCREEN_HEIGHT});
    return game;
}

void webTearDown() {
    emscripten_cancel_main_loop();
    CloseWindow();
}

void webLoop() {
    if (!getGameInstance().webRun()) {
        webTearDown();
    }
}

#endif

int main(int argc, char* argv[]) {

    std::string testArg = argc > 1 ? argv[1] : "";
    if (testArg == "test") {
        std::cout << "Running tests\n";
        if (!ComponentTest()) {
            return -1;
        }

        if (!ecsTests()) {
            return -1;
        }
        std::cout << "All tests successfull\n";

        if (argc > 2) {
            return 0;
        }
    }

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(webLoop, 0, 1);
#else
    GameOptions gameOptions(SCREEN_WIDTH, SCREEN_HEIGHT);
    Game game(gameOptions);
    game.run();
#endif

    return 0;
}
