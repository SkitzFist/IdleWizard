#ifndef IDLE_WIZARD_SYSTEMS_H
#define IDLE_WIZARD_SYSTEMS_H

#include <array>
#include <bitset>
#include <memory>

#include "System.h"
#include "Timer.h"

// debug
#include <iostream>

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
};

struct Systems {
    SystemController<UpdateSystem, UpdateSystemType, (size_t)UpdateSystemType::COUNT> updateSystems;
    SystemController<RenderSystem, RenderSystemType, (size_t)RenderSystemType::COUNT> renderSystems;
    SystemController<UiSystem, UiSystemType, (size_t)UiSystemType::COUNT> uiSystems;

    std::array<double, (size_t)UpdateSystemType::COUNT> updateMeasures;
    std::array<double, (size_t)RenderSystemType::COUNT> renderMeasures;
    std::array<double, (size_t)UiSystemType::COUNT> uiUpdateMeasures;
    std::array<double, (size_t)UiSystemType::COUNT> uiRenderMeasures;
    SystemTimer timer;
    int frameCounter = 0;
    int framesBeforeLog = 10000;

    void printMeasures() {
        frameCounter = 0;
        std::cout << "\n-------------\n";

        std::cout << "Update Systems:\n";
        for (size_t i = 0; i < updateMeasures.size(); ++i) {
            std::cout << "\t" << toString((UpdateSystemType)i) << "  Total: " << updateMeasures[i] << "  Average: " << (updateMeasures[i] / framesBeforeLog) << "\n";
            updateMeasures[i] = 0;
        }

        std::cout << "Render Systems:\n";
        for (size_t i = 0; i < renderMeasures.size(); ++i) {
            std::cout << "\t" << toString((RenderSystemType)i) << "  Total: " << renderMeasures[i] << "  Average: " << (renderMeasures[i] / framesBeforeLog) << "\n";
            renderMeasures[i] = 0;
        }

        std::cout << "Ui Update Systems:\n";
        for (size_t i = 0; i < uiUpdateMeasures.size(); ++i) {
            std::cout << "\t" << toString((UiSystemType)i) << "  Total: " << uiUpdateMeasures[i] << "  Average: " << (uiUpdateMeasures[i] / framesBeforeLog) << "\n";
            uiUpdateMeasures[i] = 0;
        }

        std::cout << "Ui Render Systems:\n";
        for (size_t i = 0; i < uiRenderMeasures.size(); ++i) {
            std::cout << "\t" << toString((UiSystemType)i) << "  Total: " << uiRenderMeasures[i] << "  Average: " << (uiRenderMeasures[i] / framesBeforeLog) << "\n";
            uiRenderMeasures[i] = 0;
        }
    }

    void runUpdateSystems(float dt) {
        for (size_t i = 0; i < updateSystems.systems.size(); ++i) {
            if (updateSystems.onOffBits.test(i) && updateSystems.systems[i]) {
                auto start = timer.begin();
                updateSystems.systems[i]->update(dt);
                updateMeasures[i] += timer.getDuration(start);
            }
        }
    }

    void runRenderSystems() {
        for (size_t i = 0; i < renderSystems.systems.size(); ++i) {
            if (renderSystems.onOffBits.test(i) && renderSystems.systems[i]) {
                auto start = timer.begin();
                renderSystems.systems[i]->render();
                renderMeasures[i] += timer.getDuration(start);
            }
        }
    }

    void updateUiSystems(float dt) {
        for (size_t i = 0; i < uiSystems.systems.size(); ++i) {
            if (uiSystems.onOffBits.test(i) && uiSystems.systems[i]) {
                auto start = timer.begin();
                uiSystems.systems[i]->update(dt);
                uiUpdateMeasures[i] += timer.getDuration(start);
            }
        }
    }

    void renderUiSystems() {
        for (size_t i = 0; i < uiSystems.systems.size(); ++i) {
            if (uiSystems.onOffBits.test(i) && uiSystems.systems[i]) {
                auto start = timer.begin();
                uiSystems.systems[i]->render();
                uiRenderMeasures[i] += timer.getDuration(start);
            }
        }
    }
};

#endif
