#include "text-screen.h"
#include "raylib.h"

TextScreen::TextScreen(int fontSize) : m_fontSize { fontSize } {}

TextScreen::TextScreen(const char *text, int fontSize)
    : m_text { text }, m_fontSize { fontSize } {}

void TextScreen::render() {
    int textWidth { MeasureText(m_text.c_str(), m_fontSize) };
    DrawText(m_text.c_str(), (GetScreenWidth() - textWidth) / 2,
             GetScreenHeight() / 2, m_fontSize, WHITE);
}
