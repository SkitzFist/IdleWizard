#ifndef IDLE_WIZARD_RENDER_BLOB_SYSTEM_H
#define IDLE_WIZARD_RENDER_BLOB_SYSTEM_H

#include <vector>

#include "raylib.h"

#include "Component.h"
#include "EntityType.h"
#include "EntityTypeMap.h"
#include "System.h"

/*
  Note: this was for testing purposes.
        real thing should probably be a RenderTextureSystem,
        and would render the correct texture instead of making an ifCheck
        to see if it's the right type. Maybe have an unordered_map with entityTypes as well.
*/

class RenderBlobSystem : public RenderSystem {
  public:
    RenderBlobSystem(std::vector<int>& blobIds, Component& positions, Component& sizes, EntityTypeMap& typeMap);

    virtual void render() const override;

  private:
    Component& m_positions;
    Component& m_sizes;
    std::vector<int>& m_blobIds;
    EntityTypeMap& m_typeMap;
    Texture2D m_blobTexture;
};

RenderBlobSystem::RenderBlobSystem(std::vector<int>& blobIds,
                                   Component& positions,
                                   Component& sizes,
                                   EntityTypeMap& typeMap) : m_blobIds(blobIds),
                                                             m_positions(positions),
                                                             m_sizes(sizes),
                                                             m_typeMap(typeMap) {
    const float size = 10.f;
    RenderTexture2D target = LoadRenderTexture(size, size);
    BeginTextureMode(target);
    ClearBackground(BLANK);
    DrawRectangle(0.f, 0.f, size, size, WHITE);
    EndTextureMode();
    m_blobTexture = target.texture;
}

void RenderBlobSystem::render() const {
    Rectangle src = {0.f, 0.f, 10.f, 10.f};
    Rectangle dst = {0.f, 0.f, 0.f, 0.f};
    Vector2 origin = {0.f, 0.f};
    for (const int id : m_blobIds) {
        const Vector2& pos = m_positions.getFromId<Vector2>(id);
        const Vector2& size = m_sizes.getFromId<Vector2>(id);
        dst.x = pos.x;
        dst.y = pos.y;
        dst.width = size.x;
        dst.height = size.y;
        DrawTexturePro(m_blobTexture, src, dst, origin, 0.f, RED);
    }
}

#endif
