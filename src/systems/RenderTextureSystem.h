#ifndef IDLE_WIZARD_RENDER_TEXTURE_SYSTEM_H
#define IDLE_WIZARD_RENDER_TEXTURE_SYSTEM_H

#include <vector>

#include "raylib.h"

#include "Component.h"
#include "System.h"
#include "EntityType.h"

class RenderManaAltar : public RenderSystem{
public:
  RenderManaAltar(Component& positions,
                      Component& sizes,
                      Component& colors,
                      std::vector<EntityType>& entityTypes);

  virtual void run() const override;

private:
  Component& positions;
  Component& sizes;
  Component& colors;
  std::vector<EntityType>& entityTypes;
};

RenderManaAltar::RenderManaAltar(Component &positions,
                                         Component &sizes,
                                         Component &colors,
                                         std::vector<EntityType> &entityTypes) : positions(positions),
                                                                                 sizes(sizes),
                                                                                 colors(colors),
                                                                                 entityTypes(entityTypes){}

void RenderManaAltar::run() const{
  
}

#endif
