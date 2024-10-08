#include "ManaAltar.h"

#include "raylib.h"

#include "ComponentType.h"
#include "EcsManager.h"
#include "EntityType.h"

void createManaAltar(EcsManager &ecs, int worldWidth, int worldHeight){
  int entityId = ecs.createEntity(EntityType::MANA_ALTAR);
  
  Vector2 size = {MANA_ALTAR_WIDTH, MANA_ALTAR_HEIGHT};
  ecs.addComponent(entityId, ComponentType::SIZE, &size);

  Vector2 pos = {worldWidth / 2.f, worldHeight / 2.f};
  ecs.addComponent(entityId, ComponentType::POSITION, &pos);

  Color color = BLUE;
  ecs.addComponent(entityId, ComponentType::COLOR, &color);
}
