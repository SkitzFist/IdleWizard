#ifndef IDLE_WIZARD_WORLD_TO_REAL_POS_SYSTEM_H
#define IDLE_WIZARD_WORLD_TO_REAL_POS_SYSTEM_H

#include "Component.h"
#include "System.h"
#include "Worlds.h"

class WorldToRealPosSystem : public UpdateSystem {
  public:
    WorldToRealPosSystem(Worlds& worlds, Component& positions, Component& worldPositions, Component& worldIndexes, Component& sizes);
    virtual ~WorldToRealPosSystem() override {};
    virtual void update(const float dt) override;

  private:
    Worlds& m_worlds;
    Component& m_positions;
    Component& m_worldPositions;
    Component& m_worldIndexes;
    Component& m_sizes;
};

#endif
