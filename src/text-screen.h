#pragma once

#include "game-state.h"
#include <string>

class TextScreen : public GameState {
  private:
    static constexpr int s_defaultFontSize { 40 };

    std::string m_text;
    int m_fontSize;

  public:
    TextScreen(int fontSize = s_defaultFontSize);
    TextScreen(const char *text, int fontSize = s_defaultFontSize);
    void render() override;
};
