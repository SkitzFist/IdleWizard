#ifndef IDLE_WIZARD_SYSTEM_H
#define IDLE_WIZARD_SYSTEM_H

/*
  Todo: Unite, have one system that has a handleInput, update(float) and render() const method.
        Have just one enum class for all systems, but three bitsets that checks if a system should
        handle input, update and/or render.
  Note: Order in the enum is important, as it is the order the system will be executed in.
*/

enum class UpdateSystemType {
    VELOCITY_MOVE,
    COUNT
};

enum class RenderSystemType {
    MANA_ALTAR,
    BLOB,
    COUNT
};

class System {
  public:
    virtual ~System() = default;
};

class UpdateSystem : public System {
  public:
    virtual void update(const float dt) = 0;
};

class RenderSystem : public System {
  public:
    virtual void render() const = 0;
};

class UpdateRenderSystem : public UpdateSystem, public RenderSystem {
};

#endif
