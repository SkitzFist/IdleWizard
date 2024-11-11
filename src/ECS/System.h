#ifndef IDLE_WIZARD_SYSTEM_H
#define IDLE_WIZARD_SYSTEM_H

#include <string>

/*
  Todo: break out in separate classes
  Note: Order in the enum is important, as it is the order the system will be executed in.
*/

enum class UpdateSystemType {
    WORLD_TO_REAL_POS,
    VELOCITY_MOVE,
    COUNT
};

inline const std::string toString(UpdateSystemType type) {
    switch (type) {
    case UpdateSystemType::WORLD_TO_REAL_POS:
        return "World to Real Pos";

    case UpdateSystemType::VELOCITY_MOVE:
        return "Velocity Move";

    default:
        return "Update System Default";
    }
}

enum class RenderSystemType {
    MANA_ALTAR,
    BLOB,
    COUNT
};

inline const std::string toString(RenderSystemType type) {
    switch (type) {
    case RenderSystemType::MANA_ALTAR:
        return "Mana Altar";

    case RenderSystemType::BLOB:
        return "BLOB";

    default:
        return "Render System Default";
    }
}

enum class UiSystemType {
    DEBUG_ENTITY_TYPE_MAP,
    DEBUG_HIGHLIGHT_ENTITY_COMPONENTS,
    COUNT
};

inline const std::string toString(UiSystemType type) {
    switch (type) {
    case UiSystemType::DEBUG_ENTITY_TYPE_MAP:
        return "Debug Entity Type Map";
    case UiSystemType::DEBUG_HIGHLIGHT_ENTITY_COMPONENTS:
        return "Debug Highlight Entity Components";

    default:
        return "Ui System Default";
    }
}

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
