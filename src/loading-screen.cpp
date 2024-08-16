#include "loading-screen.h"
#include "game-state.h"
#include "game.h"
#include "raylib.h"
#include "text-screen.h"
#include <memory>

LoadingScreen::LoadingScreen() : TextScreen { g_loadingText } {}

std::unique_ptr<GameState> LoadingScreen::update() {
    if (IsKeyPressed(KEY_SPACE)) {
        return std::make_unique<Game>();
    }
    return std::unique_ptr<GameState> {};
}
