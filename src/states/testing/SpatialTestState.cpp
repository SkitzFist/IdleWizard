#include "SpatialTestState.h"

#include "BlobFactory.h"
#include "TreeFactory.h"
#include "Timer.h"

#include "MoveSystem.h"

inline constexpr const int numEntities = 100000;
inline constexpr const int columns = 10;
inline constexpr const int rows = 10;

inline Timer t;

SpatialTestState::SpatialTestState(const GameOptions &gameOptions) : m_tileStructure(gameOptions.SCREEN_WIDTH, gameOptions.SCREEN_HEIGHT, rows, columns),
                                                                     m_positions(sizeof(Vector2), numEntities),
                                                                     m_sizes(sizeof(Vector2), numEntities),
                                                                     m_velocities(sizeof(Vector2), numEntities){
    m_camera.offset = {0.f, 0.f};
    m_camera.target = {0.f, 0.f};
    m_camera.rotation = 0.f;
    m_camera.zoom = 1.f;

    //create blob texture
    const float blobSize = 50.f;
    RenderTexture2D target = LoadRenderTexture(blobSize, blobSize);
    BeginTextureMode(target);
    ClearBackground(BLANK);
    DrawRectangle(0.f, 0.f, blobSize, blobSize, WHITE);
    EndTextureMode();
    m_blobTexture = target.texture;

    // create tree texture
    const float treeWidth = 10.f;
    const float treeHeight = 250.f;
    target = LoadRenderTexture(treeWidth, treeHeight);

    BeginTextureMode(target);
    ClearBackground(BLANK);
    DrawRectangle(0.f, 0.f, treeWidth, treeHeight, WHITE);
    EndTextureMode();
    m_treeTexture = target.texture;

    registerComponents();

    for(int i = 0; i < numEntities; ++i){
        float x = GetRandomValue(0, m_tileStructure.tileWidth * m_tileStructure.columns - 50.f);
        float y = GetRandomValue(0, m_tileStructure.tileHeight * m_tileStructure.rows - 50.f);
        createBlobAt(m_entityManager, m_componentManager, m_positions, m_sizes, m_velocities, x, y);
    }
}

SpatialTestState::~SpatialTestState(){
}


void SpatialTestState::registerComponents() {
    // m_componentManager.registerComponent(POSITION, &m_positions);
    // m_componentManager.registerComponent(SIZE, &m_sizes);
    // m_componentManager.registerComponent(VELOCITY, &m_velocities);
}

void SpatialTestState::handleInput(){
  m_cameraInput.handleInput(m_camera);

  // remove random entity
  if (IsKeyPressed(KEY_SPACE)) {
        int index = GetRandomValue(0, (int)m_entityManager.entities.size() - 1);
        m_entityManager.destroyEntity(index, m_componentManager);
  }

  // spawn random entity
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetScreenToWorld2D(GetMousePosition(), m_camera);
        createBlobAt(m_entityManager, m_componentManager, m_positions, m_sizes, m_velocities, mousePos.x, mousePos.y);
  }

}

void SpatialTestState::update(float dt){

  //clear spatial structure
  t.begin();
  clear(m_tileStructure);
  Vector2 pos;
  Vector2 size;
  for(int i = 0; i < m_entityManager.entities.size(); ++i){
    pos = readData<Vector2>(m_positions, getIndex(m_positions, i));
    size = readData<Vector2>(m_sizes, getIndex(m_sizes, i));
    addToStructure(m_tileStructure, i, pos.x, pos.y, size.x, size.y);
  }
  sortAllElementsByWorldIndex(m_tileStructure);
  //std::cout << "Readding: " << t.getDuration() << " ms\n";

  t.begin();
  m_entitiesInRange.clear();
  setRange();
  search(m_tileStructure, m_entitiesInRange, m_range.x, m_range.y, m_range.width, m_range.height);

  //std::cout << "Seraching: " << t.getDuration() << " ms\n";

  moveEntities(m_positions, m_velocities, dt);
  bounceOnEdge(m_positions, m_sizes, m_velocities, m_tileStructure.columns * m_tileStructure.tileWidth, m_tileStructure.rows * m_tileStructure.tileHeight);

}

void SpatialTestState::render() const{
  BeginMode2D(m_camera);

  //draw entities
  Vector2 pos;
  EntityType entityType;
  for(const int id : m_entitiesInRange){
    entityType = m_entityManager.entities[id];
    int posIndex = getIndex(m_positions, id);
    const Texture2D *texture;
    Color c;
    switch (entityType) {
      case EntityType::BLOB:
          texture = &m_blobTexture;
          c = RED;
          break;
      case EntityType::TREE:
          texture = &m_treeTexture;
          c = DARKBROWN;
          break;
      default:
          break;
    }
    DrawTextureEx(*texture, readData<Vector2>(m_positions, posIndex), 0.f, 1.f, c);
  }

  EndMode2D();

  renderUi();
}


void SpatialTestState::setRange() {
    // range based on camera view
    Vector2 cameraPos = m_camera.target;
    Vector2 size = {GetScreenWidth() / m_camera.zoom, GetScreenHeight() / m_camera.zoom};
    m_range.x = cameraPos.x;
    m_range.y = cameraPos.y;
    m_range.width = size.x;
    m_range.height = size.y;
}

void SpatialTestState::renderUi() const {
    const float x = 30.f;

    const float yOffset = 30.f;
    float y = 30.f;
    int fontSize = 20;

    std::string fpsText = "Fps: " + std::to_string(GetFPS());
    DrawText(fpsText.c_str(), x, y, fontSize, RAYWHITE);

    y += yOffset;
    std::string totalEntitiesText = "Entities: " + std::to_string(m_entityManager.entities.size());
    DrawText(totalEntitiesText.c_str(), x, y, fontSize, RAYWHITE);

    y += yOffset;
    std::string entitiesInRangeText = "Entities in range: " + std::to_string(m_entitiesInRange.size());
    DrawText(entitiesInRangeText.c_str(), x, y, fontSize, RAYWHITE);
}