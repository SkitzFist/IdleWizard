#ifndef IDLE_WIZARD_SYSTEM_H
#define IDLE_WIZARD_SYSTEM_H

/*
  Todo: break out in separate classes
  Note: Order in the enum is important, as it is the order the system will be executed in.
*/

enum class UpdateSystemType {
    VELOCITY_MOVE,
    WORLD_TRANSITION,
    COUNT
};

enum class RenderSystemType {
    MANA_ALTAR,
    BLOB,
    COUNT
};

enum class UiSystemType {
    DEBUG_ENTITY_TYPE_MAP,
    DEBUG_HIGHLIGHT_ENTITY_SYSTEM,
    COUNT
};

class UpdateSystem {
  public:
    virtual ~UpdateSystem() = default;
    virtual void update(const float dt) = 0;
};

class RenderSystem {
  public:
    virtual ~RenderSystem() = default;
    virtual void render() const = 0;
};

class UiSystem {
  public:
    virtual void update(const float dt) = 0;
    virtual void render() const = 0;
    virtual ~UiSystem() = default;
};

#endif
