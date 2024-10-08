#ifndef IDLE_WIZARD_RENDER_TEXTURE_SYSTEM_H
#define IDLE_WIZARD_RENDER_TEXTURE_SYSTEM_H

#include <vector>

#include "raylib.h"

#include "Component.h"
#include "System.h"
#include "EntityType.h"
#include "ManaAltar.h"

class RenderManaAltar : public RenderSystem{
public:
  RenderManaAltar(Component &positions,
                  Component &sizes,
                  Component &colors,
                  std::vector<int> &manaAltarIds);

  virtual void run() const override;

private:
  Component& positions;
  Component& sizes;
  Component& colors;
  std::vector<int>& manaAltarIds;
  Texture2D manaAltarTexture;
};

RenderManaAltar::RenderManaAltar(Component &positions,
                                 Component &sizes,
                                 Component &colors,
                                 std::vector<int> &manaAltarIds) : positions(positions),
                                                                  sizes(sizes),
                                                                  colors(colors),
                                                                  manaAltarIds(manaAltarIds) {
  RenderTexture2D target = LoadRenderTexture(MANA_ALTAR_WIDTH, MANA_ALTAR_HEIGHT);
  const float thickness = 1.f;
  BeginTextureMode(target);
  ClearBackground(BLANK);
  DrawLineEx({0.f, 0.f}, {0.f, MANA_ALTAR_HEIGHT}, thickness, RED);
  DrawLineEx({0.f, MANA_ALTAR_HEIGHT}, {MANA_ALTAR_WIDTH, MANA_ALTAR_HEIGHT}, thickness, GREEN);
  DrawLineEx({MANA_ALTAR_WIDTH, MANA_ALTAR_HEIGHT}, {MANA_ALTAR_WIDTH, 0.f}, thickness, BLUE);
  EndTextureMode();
  manaAltarTexture = target.texture;
}

void RenderManaAltar::run() const{
  Rectangle src = {0.f, 0.f, 10.f, 10.f};
  Rectangle dst = {0.f, 0.f, 0.f, 0.f};
  Vector2 origin = {0.f, 0.f};

  for(const int id : manaAltarIds){
    Vector2& pos = positions.getFromId<Vector2>(id);
    Vector2& size = sizes.getFromId<Vector2>(id);
    Color& color = colors.getFromId<Color>(id);
    dst.x = pos.x;
    dst.y = pos.y;
    dst.width = size.x;
    dst.height = size.y;
    DrawTexturePro(manaAltarTexture, src, dst, origin, 1.f, color);
  }
}

#endif
