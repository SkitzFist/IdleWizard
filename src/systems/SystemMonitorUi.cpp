#include "SystemMonitorUi.h"

#include <string>

SystemMonitorUi::SystemMonitorUi(const GameOptions& gameOptions,
                                 Systems& systems) : m_gameOptions(gameOptions),
                                                     m_systems(systems),
                                                     m_isEnabled(true) {
}

SystemMonitorUi::~SystemMonitorUi() {}

void SystemMonitorUi::update(float dt) {
    if (IsKeyPressed(KEY_TWO)) {
        m_isEnabled = !m_isEnabled;
    }

    ++m_systems.frameCounter;
}

void SystemMonitorUi::render() const {
    if (!m_isEnabled) {
        return;
    }

    float x = 10.f;
    float y = 60.f;

    int fontSize = 20;
    float textSpacing = 1.f;

    // accumulate total text
    std::string text = "Update Systems: \n";
    for (size_t i = 0; i < m_systems.updateMeasures.size(); ++i) {
        text += "\t" + toString((UpdateSystemType)i) + ": " + std::to_string((m_systems.updateMeasures[i] / m_systems.frameCounter)) + "\n";
    }

    text += "\nRender Systems: \n";
    for (size_t i = 0; i < m_systems.renderMeasures.size(); ++i) {
        text += "\t" + toString((RenderSystemType)i) + ": " + std::to_string((m_systems.renderMeasures[i] / m_systems.frameCounter)) + "\n";
    }

    text += "\nUi Update: \n";
    for (size_t i = 0; i < m_systems.uiUpdateMeasures.size(); ++i) {
        text += "\t" + toString((UiSystemType)i) + ": " + std::to_string((m_systems.uiUpdateMeasures[i] / m_systems.frameCounter)) + "\n";
    }

    text += "\nUI Render:\n";
    for (size_t i = 0; i < m_systems.uiRenderMeasures.size(); ++i) {
        text += "\t" + toString((UiSystemType)i) + ": " + std::to_string((m_systems.uiRenderMeasures[i] / m_systems.frameCounter)) + "\n";
    }

    Vector2 textSize = MeasureTextEx(GetFontDefault(), text.c_str(), fontSize, textSpacing);

    // draw container
    const float containerSizeX = m_gameOptions.SCREEN_WIDTH * 0.33f;
    const float containerPaddingY = 10.f;
    Vector2 containerSize = {containerSizeX, textSize.y + (containerPaddingY * 2.f)};
    Vector2 containerPos = {x, y};
    Rectangle containerRect = {containerPos.x, containerPos.y, containerSize.x, containerSize.y};

    Color containerBackgroundColor = {245, 245, 245, 150};
    DrawRectangleRec(containerRect, containerBackgroundColor);

    float containerBorderThickness = 5.f;
    DrawRectangleLinesEx(containerRect, containerBorderThickness, BLACK);

    // draw text
    x += 20.f;
    y += 20.f;

    DrawText(text.c_str(), x, y, fontSize, BLACK);
}
