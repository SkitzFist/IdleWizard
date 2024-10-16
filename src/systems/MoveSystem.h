#ifndef IDLE_WIZARD_MOVE_SYSTEM_H
#define IDLE_WIZARD_MOVE_SYSTEM_H

#include "raylib.h"

#include "Component.h"
#include "System.h"
#include "TileMap.h"

/*
  Note: this was just for testing, it's quite inefficient.
*/

class MoveSystem : public UpdateSystem {
  public:
    MoveSystem(Component &positions, Component &velocities, Component &sizes, TileMap &tileMap);
    virtual void update(const float dt) override;

  private:
    Component &m_positions;
    Component &m_velocities;
    Component &m_sizes;
    TileMap &m_tileMap;
};

MoveSystem::MoveSystem(Component &positions, Component &velocities, Component &sizes, TileMap &tileMap) : m_positions(positions),
                                                                                                          m_velocities(velocities),
                                                                                                          m_sizes(sizes),
                                                                                                          m_tileMap(tileMap) {
    //
}

void MoveSystem::update(const float dt) {
    int entityID = -1;
    for (int i = 0; i < m_velocities.getSize(); ++i) {
        entityID = m_velocities[i];

        Vector2 &pos = m_positions.get<Vector2>(m_positions.getIndex(entityID));
        Vector2 &vel = m_velocities.get<Vector2>(m_velocities.getIndex(entityID));
        Vector2 &size = m_velocities.get<Vector2>(m_velocities.getIndex(entityID));

        pos.x += vel.x * dt;
        pos.y += vel.y * dt;

        if (pos.x + size.x > m_tileMap.tileWidth) {
            pos.x = -size.x;
        }

        m_tileMap.entities[i] = (static_cast<int>(pos.y) / m_tileMap.tileHeight) * COLUMNS + (static_cast<int>(pos.x) / m_tileMap.tileWidth) % (COLUMNS * ROWS);
    }
}

#endif
