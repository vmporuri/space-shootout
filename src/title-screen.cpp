#include "title-screen.h"
#include "game-state.h"
#include "raylib.h"

GameState::State TitleScreen::update() {
    if (IsKeyPressed(KEY_SPACE)) {
        return GameState::LOADING_SCREEN;
    }
    return m_stateType;
}

void TitleScreen::render() {
    int titleWidth { MeasureText(g_gameTitle, g_titleFontSize) };
    int subtitleWidth { MeasureText(g_gameSubtitle, g_subtitleFontSize) };
    DrawText(g_gameTitle, (GetScreenWidth() - titleWidth) / 2,
             GetScreenHeight() / 3, g_titleFontSize, WHITE);
    DrawText(g_gameSubtitle, (GetScreenWidth() - subtitleWidth) / 2,
             2 * GetScreenHeight() / 3, g_subtitleFontSize, WHITE);
}
