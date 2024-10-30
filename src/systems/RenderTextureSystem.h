#ifndef IDLE_WIZARD_RENDER_TEXTURE_SYSTEM_H
#define IDLE_WIZARD_RENDER_TEXTURE_SYSTEM_H

#include <vector>

#include "raylib.h"

#include "Component.h"
#include "EntityType.h"
#include "System.h"

class RenderManaAltar : public RenderSystem {
  public:
    RenderManaAltar(Component& positions,
                    Component& sizes,
                    Component& colors,
                    std::vector<EntityType>& entityTypes);

    virtual void render() const override;

  private:
    Component& positions;
    Component& sizes;
    Component& colors;
    std::vector<EntityType>& entityTypes;
};

RenderManaAltar::RenderManaAltar(Component& positions,
                                 Component& sizes,
                                 Component& colors,
                                 std::vector<EntityType>& entityTypes) : positions(positions),
                                                                         sizes(sizes),
                                                                         colors(colors),
                                                                         entityTypes(entityTypes) {}

void RenderManaAltar::render() const {
}

#endif
