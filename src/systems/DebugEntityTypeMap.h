#ifndef IDLE_WIZARD_DEBUG_ENTITY_TYPE_MAP_H
#define IDLE_WIZARD_DEBUG_ENTITY_TYPE_MAP_H

#include "raylib.h"

#include "EcsManager.h"
#include "System.h"

class DebugEntityTypeMap : public UpdateRenderSystem {
  public:
    DebugEntityTypeMap(EcsManager &ecs);
    virtual void update(float dt) override;
    virtual void render() const override;

  private:
    EcsManager &m_ecs;
    bool m_enabled;
};

#endif
