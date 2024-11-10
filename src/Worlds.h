#ifndef IDLE_WIZARD_WORLD_H
#define IDLE_WIZARD_WORLD_H

#include <vector>

#include "raylib.h"

#include "EcsManager.h"
#include "Timer.h"

inline constexpr const int MAX_COLUMNS = 4;
inline constexpr const int MAX_ROWS = 4;

struct Worlds {
    std::vector<Vector2> positions;

    int columns, rows;
    float width, height;

    bool isInTransition;
    Timer transitionTimer;
};

Worlds createWorlds(int columns, int rows, float width, float height);

void split(Worlds& worlds, EcsManager& ecs);
void grow(Worlds& worlds, EcsManager& ecs);
void transition(Worlds& worlds);

#endif
