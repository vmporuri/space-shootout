#include "title-screen.h"
#include "game-state.h"
#include "raylib.h"

GameState::State TitleScreen::update() {
    if (IsKeyPressed(KEY_SPACE)) {
        return GameState::GAME;
    }
    return m_stateType;
}

void TitleScreen::render() {
    DrawText(g_gameTitle, GetScreenWidth() / 6, GetScreenHeight() / 3,
             g_titleFontSize, WHITE);
    DrawText(g_gameSubtitle, GetScreenWidth() / 4, 2 * GetScreenHeight() / 3,
             g_subtitleFontSize, WHITE);
}
