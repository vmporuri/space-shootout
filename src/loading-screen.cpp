#include "loading-screen.h"
#include "game-state.h"
#include "raylib.h"

GameState::State LoadingScreen::update() {
    if (IsKeyPressed(KEY_SPACE)) {
        return GameState::GAME;
    }
    return m_stateType;
}

void LoadingScreen::render() {
    int loadingTextWidth { MeasureText(g_loadingText, g_loadingFontSize) };
    DrawText(g_loadingText, (GetScreenWidth() - loadingTextWidth) / 2,
             GetScreenHeight() / 2, g_loadingFontSize, WHITE);
}
