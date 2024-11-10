#include "ManaAltar.h"

#include "raylib.h"

#include "ComponentType.h"
#include "EcsManager.h"
#include "EntityType.h"
#include "Vector2i.h"

void createManaAltar(EcsManager& ecs, Worlds& worlds) {
    int entityId = ecs.createEntity(EntityType::MANA_ALTAR);

    Vector2 size = {MANA_ALTAR_WIDTH, MANA_ALTAR_HEIGHT};
    ecs.addComponent(entityId, ComponentType::SIZE, &size);

    Vector2 worldPos = {GetRandomValue(10, 90) / 100.f, GetRandomValue(10, 90) / 100.f};
    ecs.addComponent(entityId, ComponentType::WORLD_POSITION, &worldPos);

    int worldIndex = 0;
    ecs.addComponent(entityId, ComponentType::WORLD_INDEX, &worldIndex);

    Vector2 pos = {0.f, 0.f};
    ecs.addComponent(entityId, ComponentType::POSITION, &pos);

    Color color = {
        (unsigned char)(GetRandomValue(0, 255)),
        (unsigned char)(GetRandomValue(0, 255)),
        (unsigned char)(GetRandomValue(0, 255)),
        255};
    ecs.addComponent(entityId, ComponentType::COLOR, &color);

    Vector2i resource = {0, 100};
    ecs.addComponent(entityId, ComponentType::RESOURCE, &resource);
}
