#ifndef IDLE_WIZARD_SYSTEMS_H
#define IDLE_WIZARD_SYSTEMS_H

#include <array>
#include <bitset>
#include <memory>

#include "System.h"

template <class System, typename SystemTypeEnum, std::size_t size>
struct SystemController {
    std::array<std::unique_ptr<System>, size> systems;
    std::bitset<size> onOffBits;

    ~SystemController() = default;

    template <typename T, typename... Args>
    void add(SystemTypeEnum type, Args&&... args) {
        systems[(int)type] = std::make_unique<T>(std::forward<Args>(args)...);
        enableSystem(type);
    }

    void enableSystem(SystemTypeEnum type) {
        onOffBits.set((int)type);
    }

    void disableSystem(SystemTypeEnum type) {
        onOffBits.reset((int)type);
    }

    void disableAll() {
        onOffBits.reset();
    }

    void update(float dt) {
        for (size_t i = 0; i < systems.size(); ++i) {
            if (onOffBits.test(i) && systems[i]) {
                systems[i]->update(dt);
            }
        }
    }

    void render() {
        for (size_t i = 0; i < systems.size(); ++i) {
            if (onOffBits.test(i) && systems[i]) {
                systems[i]->render();
            }
        }
    }
};

struct Systems {
    SystemController<UpdateSystem, UpdateSystemType, (size_t)UpdateSystemType::COUNT> updateSystems;
    SystemController<RenderSystem, RenderSystemType, (size_t)RenderSystemType::COUNT> renderSystems;
    SystemController<UiSystem, UiSystemType, (size_t)UiSystemType::COUNT> uiSystems;
};

#endif
