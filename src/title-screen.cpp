#include "title-screen.h"
#include "loading-screen.h"
#include "raylib.h"
#include <memory>

TitleScreen::TitleScreen() : TextScreen { g_loadingText } {}

std::unique_ptr<GameState> TitleScreen::update() {
    if (IsKeyPressed(KEY_SPACE)) {
        return std::make_unique<LoadingScreen>();
    }
    return std::unique_ptr<GameState> {};
}

void TitleScreen::render() {
    int titleWidth { MeasureText(g_gameTitle, g_titleFontSize) };
    int subtitleWidth { MeasureText(g_gameSubtitle, g_subtitleFontSize) };
    DrawText(g_gameTitle, (GetScreenWidth() - titleWidth) / 2,
             GetScreenHeight() / 3, g_titleFontSize, WHITE);
    DrawText(g_gameSubtitle, (GetScreenWidth() - subtitleWidth) / 2,
             2 * GetScreenHeight() / 3, g_subtitleFontSize, WHITE);
}
