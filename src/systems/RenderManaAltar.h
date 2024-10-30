#ifndef IDLE_WIZARD_RENDER_TEXTURE_SYSTEM_H
#define IDLE_WIZARD_RENDER_TEXTURE_SYSTEM_H

#include <string>
#include <vector>

#include "raylib.h"

#include "Component.h"
#include "EntityType.h"
#include "ManaAltar.h"
#include "Resource.h"
#include "System.h"

class RenderManaAltar : public RenderSystem {
  public:
    RenderManaAltar(Component& positions,
                    Component& sizes,
                    Component& colors,
                    Component& resources,
                    std::vector<int>& manaAltarIds);
    virtual ~RenderManaAltar() override;

    virtual void render() const override;

  private:
    Component& positions;
    Component& sizes;
    Component& colors;
    Component& resources;
    std::vector<int>& manaAltarIds;
    Texture2D manaAltarTexture;
};

RenderManaAltar::RenderManaAltar(Component& positions,
                                 Component& sizes,
                                 Component& colors,
                                 Component& resources,
                                 std::vector<int>& manaAltarIds) : positions(positions),
                                                                   sizes(sizes),
                                                                   colors(colors),
                                                                   resources(resources),
                                                                   manaAltarIds(manaAltarIds) {
    std::cout << "LoadingTexture\n";
    manaAltarTexture = LoadTexture("Assets/mana_altar_sh.png");
}

RenderManaAltar::~RenderManaAltar() {
    UnloadTexture(manaAltarTexture);
}

void RenderManaAltar::render() const {
    const float textureSize = 64.f;
    const float scale = 2.f;
    float srcHeight = 0.f;
    float dstHeight = 0.f;
    float fillLevel = 0;
    const float startFillLevel = 0.25f;
    const float maxFillLevel = 1.f;
    int fontSize = 24;
    float spacing = 1.f;
    Rectangle src = {0.f, 0.f, textureSize, textureSize};
    Rectangle dst = {0.f, 0.f, 0.f, 0.f};
    Vector2 origin = {0.f, 0.f};
    std::string text;
    Vector2 textSize;
    Vector2 textPos;

    for (const int id : manaAltarIds) {
        Vector2& pos = positions.getFromId<Vector2>(id);
        Vector2& size = sizes.getFromId<Vector2>(id);
        Color& color = colors.getFromId<Color>(id);
        Resource& resource = resources.getFromId<Resource>(id);

        // draw base
        src = {0.f, 0.f, textureSize, textureSize};
        dst = {pos.x, pos.y, size.x, size.y};
        DrawTexturePro(manaAltarTexture, src, dst, origin, 0.f, WHITE);

        // draw filling
        fillLevel = static_cast<float>(resource.current) / static_cast<float>(resource.max);
        float fillScale = startFillLevel + (maxFillLevel - startFillLevel) * fillLevel;

        if (fillLevel > 0.0f) {
            srcHeight = fillScale * textureSize;
            dstHeight = fillScale * size.y;

            src.y = textureSize + (textureSize - srcHeight);
            src.height = srcHeight;

            dst.y = pos.y + (size.y - dstHeight);
            dst.height = dstHeight;

            DrawTexturePro(manaAltarTexture, src, dst, origin, 0.f, color);
        }

        // draw text
        src = {0.f, textureSize * 2.f, textureSize, textureSize};
        dst = {pos.x, pos.y, size.x, size.y};
        DrawTexturePro(manaAltarTexture, src, dst, origin, 0.f, WHITE);
        text = std::to_string(resource.current);
        textSize = MeasureTextEx(GetFontDefault(), text.c_str(), fontSize, spacing);
        textPos = {dst.x + (size.x / 2.f - textSize.x / 2.f), dst.y + (size.y / 8.f - textSize.y / 3.f)};
        DrawTextPro(
            GetFontDefault(),
            text.c_str(),
            textPos,
            {0.f, 0.f},
            0.f,
            fontSize,
            spacing,
            BLACK);
    }
}

#endif
