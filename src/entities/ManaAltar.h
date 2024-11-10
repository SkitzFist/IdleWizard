#ifndef IDLE_WIZARD_MANA_ALTAR_H
#define IDLE_WIZARD_MANA_ALTAR_H

#include "Worlds.h"

constexpr const float MANA_ALTAR_WIDTH = 256.f / 2.f;
constexpr const float MANA_ALTAR_HEIGHT = 256.f / 2.f;

class EcsManager;
void createManaAltar(EcsManager& ecs, Worlds& worlds);

#endif
