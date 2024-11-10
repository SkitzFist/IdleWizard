#ifndef IDLE_WIZARD_MOVE_SYSTEM_H
#define IDLE_WIZARD_MOVE_SYSTEM_H

#include "raylib.h"

#include "Component.h"
#include "System.h"

/*
  Note: this was just for testing, it's quite inefficient.
*/

class MoveSystem : public UpdateSystem {
  public:
    MoveSystem(Component& positions, Component& velocities, Component& sizes);
    virtual ~MoveSystem() override {}
    virtual void update(const float dt) override;

  private:
    Component& m_positions;
    Component& m_velocities;
    Component& m_sizes;
};

MoveSystem::MoveSystem(Component& positions, Component& velocities, Component& sizes) : m_positions(positions),
                                                                                        m_velocities(velocities),
                                                                                        m_sizes(sizes) {
    //
}

void MoveSystem::update(const float dt) {
    int entityID = -1;
    for (int i = 0; i < m_velocities.getSize(); ++i) {
        entityID = m_velocities[i];

        Vector2& pos = m_positions.get<Vector2>(m_positions.getIndex(entityID));
        Vector2& vel = m_velocities.get<Vector2>(m_velocities.getIndex(entityID));
        Vector2& size = m_velocities.get<Vector2>(m_velocities.getIndex(entityID));

        pos.x += vel.x * dt;
        pos.y += vel.y * dt;
    }
}

#endif
