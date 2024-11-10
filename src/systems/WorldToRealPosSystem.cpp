#include "WorldToRealPosSystem.h"
#include "MathHack.hpp"

WorldToRealPosSystem::WorldToRealPosSystem(Worlds& worlds,
                                           Component& positions,
                                           Component& worldPositions,
                                           Component& worldIndexes,
                                           Component& sizes) : m_worlds(worlds),
                                                               m_positions(positions),
                                                               m_worldPositions(worldPositions),
                                                               m_worldIndexes(worldIndexes),
                                                               m_sizes(sizes) {
}

// Todo simd
void WorldToRealPosSystem::update(float dt) {
    for (int i = 0; i < m_worldPositions.getSize(); ++i) {
        int entityId = m_worldPositions[i];

        int worldIndex = m_worldIndexes.getFromId<int>(entityId);

        const Vector2& worldPos = m_worldPositions.getFromId<Vector2>(entityId);
        Vector2& position = m_positions.getFromId<Vector2>(entityId);

        const Vector2& worldsPos = m_worlds.positions[worldIndex];

        position.x = worldsPos.x + (worldPos.x * m_worlds.width);
        position.y = worldsPos.y + (worldPos.y * m_worlds.height);
    }
}