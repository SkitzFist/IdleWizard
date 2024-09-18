#include "ComponentManager.h"
#include "ComponentType.h"
#include "EntityManager.h"
#include "EntityType.h"

#include "Component.h"
#include "ComponentUtils.h"

#include "TileStructure.h"

inline constexpr const float TREE_WIDTH = 10.f;
inline constexpr const float TREE_HEIGHT = 250.f;

inline const void createTreeAt(EntityManager &entityManager,
                             ComponentManager &componentManager,
                             Component &positions,
                             Component &sizes,
                             float x,
                             float y) {

    int entityId = entityManager.createEntity(EntityType::TREE);
    componentManager.createEntity();

    add(positions, entityId, Vector2{x, y});
    componentManager.addComponentToEntity(entityId, ComponentType::POSITION);

    add(sizes, entityId, Vector2{TREE_WIDTH, TREE_HEIGHT});
    componentManager.addComponentToEntity(entityId, ComponentType::SIZE);
}