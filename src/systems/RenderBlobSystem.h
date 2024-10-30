#ifndef IDLE_WIZARD_RENDER_BLOB_SYSTEM_H
#define IDLE_WIZARD_RENDER_BLOB_SYSTEM_H

#include <vector>

#include "raylib.h"

#include "Component.h"
#include "EntityType.h"
#include "EntityTypeMap.h"
#include "System.h"

class RenderBlobSystem : public RenderSystem {
  public:
    RenderBlobSystem(std::vector<int>& blobIds, Component& positions, Component& sizes, EntityTypeMap& typeMap);
    virtual ~RenderBlobSystem() override;
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
    m_blobTexture = LoadTexture("Assets/wizard.png");
}

RenderBlobSystem::~RenderBlobSystem() {
    UnloadTexture(m_blobTexture);
}

void RenderBlobSystem::render() const {
    Rectangle src = {0.f, 0.f, 32.f, 32.f};
    Rectangle dst = {0.f, 0.f, 0.f, 0.f};
    Vector2 origin = {0.f, 0.f};
    for (const int id : m_blobIds) {
        const Vector2& pos = m_positions.getFromId<Vector2>(id);
        const Vector2& size = m_sizes.getFromId<Vector2>(id);
        dst.x = pos.x;
        dst.y = pos.y;
        dst.width = 32.f * 3.f;
        dst.height = 32.f * 3.f;
        DrawTexturePro(m_blobTexture, src, dst, origin, 0.f, WHITE);
    }
}

#endif
