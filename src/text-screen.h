#pragma once

#include "game-state.h"
#include "raylib.h"
#include <memory>
#include <string>

const int g_defaultFontSize { 40 };

class TextScreen : public GameState {
  private:
    std::string m_text;
    int m_fontSize;

  public:
    TextScreen(const char *text, int fontSize = g_defaultFontSize)
        : m_text { text }, m_fontSize { fontSize } {}
    std::unique_ptr<GameState> update() override { return { nullptr }; }
    void render() override {
        int textWidth { MeasureText(m_text.c_str(), m_fontSize) };
        DrawText(m_text.c_str(), (GetScreenWidth() - textWidth) / 2,
                 GetScreenHeight() / 2, m_fontSize, WHITE);
    }
};
