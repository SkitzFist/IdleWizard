#ifndef IDLE_WIZARD_SYSTEMS_H
#define IDLE_WIZARD_SYSTEMS_H

#include <array>
#include <bitset>
#include <memory>

#include "System.h"

struct Systems {
    std::array<std::unique_ptr<UpdateSystem>, (int)UpdateSystemType::COUNT> updateSystems;
    std::array<std::unique_ptr<RenderSystem>, (int)RenderSystemType::COUNT> renderSystems;

    std::bitset<(int)UpdateSystemType::COUNT> updateSystemBits;
    std::bitset<(int)RenderSystemType::COUNT> renderSystemBits;

    template <typename T, typename... Args>
    void registerUpdateSystem(UpdateSystemType type, Args&&... args) {
        static_assert(std::is_base_of<UpdateSystem, T>::value, "T must derive from UpdateSystem");
        updateSystems[(int)type] = std::make_unique<T>(std::forward<Args>(args)...);
        enableUpdateSystem(type);
    }

    template <typename T, typename... Args>
    void registerRenderSystem(RenderSystemType type, Args&&... args) {
        static_assert(std::is_base_of<RenderSystem, T>::value, "T must derive from RenderSystem");
        renderSystems[(int)type] = std::make_unique<T>(std::forward<Args>(args)...);
        enableRenderSystem(type);
    }

    void enableUpdateSystem(UpdateSystemType type) {
        updateSystemBits.set((int)type);
    }

    void enableRenderSystem(RenderSystemType type) {
        renderSystemBits.set((int)type);
    }

    void disableUpdateSystem(UpdateSystemType type) {
        updateSystemBits.reset((int)type);
    }

    void disableRenderSystem(RenderSystemType type) {
        renderSystemBits.reset((int)type);
    }

    void disableAllUpdateSystems() {
        updateSystemBits.reset();
    }

    void disableAllRenderSystems() {
        renderSystemBits.reset();
    }

    void runUpdateSystems(const float dt) {
        for (size_t i = 0; i < updateSystems.size(); ++i) {
            if (updateSystemBits.test(i) && updateSystems[i]) {
                updateSystems[i]->update(dt);
            }
        }
    }

    void runRenderSystems() {
        for (size_t i = 0; i < renderSystems.size(); ++i) {
            if (renderSystemBits.test(i) && renderSystems[i]) {
                renderSystems[i]->render();
            }
        }
    }
};

#endif
