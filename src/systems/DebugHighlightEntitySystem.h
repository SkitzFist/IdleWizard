#ifndef DEBUG_HIGHLIGHT_ENITTY_SYSTEM_H
#define DEBUG_HIGHLIGHT_ENITTY_SYSTEM_H

#include <vector>

#include "raylib.h"

#include "EcsManager.h"
#include "System.h"

class DebugHighlightEntitySystem : public UiSystem {
  public:
    DebugHighlightEntitySystem(EcsManager& EcsManager, Camera2D& camera);
    virtual ~DebugHighlightEntitySystem() override {}

    virtual void update(float dt) override;
    virtual void render() const override;

  private:
    EcsManager& m_ecs;
    Components& m_components;
    Camera2D& m_camera;
    std::vector<int> m_entities;
};

#endif