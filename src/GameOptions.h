#ifndef IDLE_MINER_GAME_OPTIONS_H_
#define IDLE_MINER_GAME_OPTIONS_H_

struct GameOptions {
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;

    GameOptions(const int screenWidth, const int screenHeight) : SCREEN_WIDTH(screenWidth), SCREEN_HEIGHT(screenHeight) {}
};

#endif
