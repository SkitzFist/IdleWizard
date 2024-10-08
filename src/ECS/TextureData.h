#ifndef IDLE_WIZARD_TEXTURE_DATA_H
#define IDLE_WIZARD_TEXTURE_DATA_H

#include <array>

#include "raylib.h"

#include "EntityType.h"

//tmp until real textures has been added
#include "ManaAltar.h"

struct TextureData{
  std::array<Texture2D, static_cast<int>(EntityType::COUNT)> textures;

  TextureData(){
    createManaAltarTexture();
  }

private:
  void createManaAltarTexture(){
      RenderTexture2D target = LoadRenderTexture(MANA_ALTAR_WIDTH, MANA_ALTAR_HEIGHT);
      const float thickness = 10.f;
      BeginTextureMode(target);
      ClearBackground(BLANK);
      DrawLineEx({0.f,0.f}, {0.f, MANA_ALTAR_HEIGHT}, thickness, BLACK);
      DrawLineEx({0.f, MANA_ALTAR_HEIGHT}, {MANA_ALTAR_WIDTH, MANA_ALTAR_HEIGHT}, thickness, BLACK);
      DrawLineEx({MANA_ALTAR_WIDTH, MANA_ALTAR_HEIGHT},{MANA_ALTAR_WIDTH, 0.f}, thickness, BLACK);
      EndTextureMode();

      textures[(int)EntityType::MANA_ALTAR] = target.texture;
  }

  void createBlobTexture(){
      const float blobSize = 50.f;
      RenderTexture2D target = LoadRenderTexture(blobSize, blobSize);
      BeginTextureMode(target);
      ClearBackground(BLANK);
      DrawRectangle(0.f, 0.f, blobSize, blobSize, WHITE);
      EndTextureMode();
      
      textures[(int)EntityType::BLOB] = target.texture;
  }

};

#endif
