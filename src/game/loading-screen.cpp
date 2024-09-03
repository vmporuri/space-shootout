#include "loading-screen.h"
#include "game-state.h"
#include "game.h"
#include "text-screen.h"
#include <memory>

LoadingScreen::LoadingScreen() : TextScreen { s_loadingText } {}

LoadingScreen::LoadingScreen(GameState &oldState)
    : TextScreen(oldState, s_loadingText) {}

std::unique_ptr<GameState> LoadingScreen::update() {
    if (m_peerConn->findPeer()) {
        return std::make_unique<Game>(*this);
    }
    return nullptr;
}
