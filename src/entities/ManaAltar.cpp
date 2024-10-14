#include "ManaAltar.h"

#include "raylib.h"

#include "ComponentType.h"
#include "EcsManager.h"
#include "EntityType.h"
#include "Vector2i.h"

void createManaAltar(EcsManager &ecs, int worldWidth, int worldHeight){
  int entityId = ecs.createEntity(EntityType::MANA_ALTAR);
  
  Vector2 size = {MANA_ALTAR_WIDTH, MANA_ALTAR_HEIGHT};
  ecs.addComponent(entityId, ComponentType::SIZE, &size);

  Vector2 pos = {worldWidth / 2.f, worldHeight / 2.f};
  ecs.addComponent(entityId, ComponentType::POSITION, &pos);

  Color color = {
      (unsigned char)(GetRandomValue(0, 255)),
      (unsigned char)(GetRandomValue(0, 255)),
      (unsigned char)(GetRandomValue(0, 255)),
      255
  };
  ecs.addComponent(entityId, ComponentType::COLOR, &color);

  Vector2i resource = {0, 100};
  ecs.addComponent(entityId, ComponentType::RESOURCE, &resource);
}
