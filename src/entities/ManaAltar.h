#ifndef IDLE_WIZARD_MANA_ALTAR_H
#define IDLE_WIZARD_MANA_ALTAR_H

constexpr const float MANA_ALTAR_WIDTH = 256.f;
constexpr const float MANA_ALTAR_HEIGHT = 256.f;

class EcsManager;
void createManaAltar(EcsManager& ecs, const int worldWidth, const int worldHeight);

#endif
