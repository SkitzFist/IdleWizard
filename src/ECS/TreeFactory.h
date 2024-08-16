#include "ComponentManager.h"
#include "ComponentType.h"
#include "EntityManager.h"
#include "EntityType.h"

#include "VectorComponent.h"

#include "TileStructure.h"

inline constexpr const float TREE_WIDTH = 50.f;
inline constexpr const float TREE_HEIGHT = 250.f;

inline const void createTree(EntityManager &entityManager,
                             ComponentManager &componentManager,
                             VectorComponent &positions,
                             VectorComponent &sizes,
                             TileStructure &tileStructure,
                             float minX,
                             float minY) {

    int entityId = entityManager.createEntity(EntityType::TREE);
    componentManager.createEntity();

    float min = minX;
    float max = tileStructure.currentMaxWidth() - TREE_WIDTH;
    float x = static_cast<float>(GetRandomValue(min, max));

    min = minY;
    max = tileStructure.currentMaxHeight() - TREE_HEIGHT;
    float y = static_cast<float>(GetRandomValue(min, max));
    positions.add(entityId, x, y);
    componentManager.addComponent(entityId, ComponentType::POSITION);

    sizes.add(entityId, TREE_WIDTH, TREE_HEIGHT);
    componentManager.addComponent(entityId, ComponentType::SIZE);
}