#ifndef IDLE_WIZARD_RENDER_BLOB_SYSTEM_H
#define IDLE_WIZARD_RENDER_BLOB_SYSTEM_H

#include <vector>

#include "raylib.h"

#include "EntityType.h"
#include "System.h"
#include "Component.h"

/*
  Note: this was for testing purposes.
        real thing should probably be a RenderTextureSystem,
        and would render the correct texture instead of making an ifCheck
        to see if it's the right type. Maybe have an unordered_map with entityTypes as well.
*/

class RenderBlobSystem : public RenderSystem{
public:
  RenderBlobSystem(std::vector<EntityType>& entityTypes, Component& positions, Component& sizes);

  virtual void run() const override;
private:
  std::vector<EntityType>& m_entityTypes;
  Component& m_positions;
  Component& m_sizes;
  Texture2D m_blobTexture;
};

RenderBlobSystem::RenderBlobSystem(std::vector<EntityType> &entityTypes, Component &positions, Component &sizes) : m_entityTypes(entityTypes),
                                                                                                                   m_positions(positions),
                                                                                                                   m_sizes(sizes) {
  const float size = 10.f;
  RenderTexture2D target = LoadRenderTexture(size, size);
  BeginTextureMode(target);
  ClearBackground(BLANK);
  DrawRectangle(0.f, 0.f, size, size, WHITE);
  EndTextureMode();
  m_blobTexture = target.texture;
}

void RenderBlobSystem::run() const {
  Rectangle src = {0.f, 0.f, 10.f, 10.f};
  Rectangle dst = {0.f,0.f,0.f,0.f};
  Vector2 origin = {0.f, 0.f};
  for(int i = 0; i < m_entityTypes.size(); ++i){
    if(m_entityTypes[i] == EntityType::BLOB){
            const Vector2& pos = m_positions.get<Vector2>(i);
            const Vector2& size = m_sizes.get<Vector2>(i);
            dst.x = pos.x;
            dst.y = pos.y;
            dst.width = size.x;
            dst.height = size.y;
            DrawTexturePro(m_blobTexture, src, dst, origin, 0.f, RED);
    }
  }
}

#endif
