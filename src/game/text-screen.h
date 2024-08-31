#pragma once

#include "game-state.h"
#include "raylib.h"
#include <string>

class TextScreen : public GameState {
  private:
    static constexpr int s_defaultFontSize { 40 };

    std::string m_text;
    int m_fontSize;

  public:
    TextScreen(int fontSize = s_defaultFontSize) : m_fontSize { fontSize } {}
    TextScreen(const char *text, int fontSize = s_defaultFontSize)
        : m_text { text }, m_fontSize { fontSize } {}
    void render() override {
        int textWidth { MeasureText(m_text.c_str(), m_fontSize) };
        DrawText(m_text.c_str(), (GetScreenWidth() - textWidth) / 2,
                 GetScreenHeight() / 2, m_fontSize, WHITE);
    }
};
