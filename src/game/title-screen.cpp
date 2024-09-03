#include "title-screen.h"
#include "game/text-screen.h"
#include "loading-screen.h"
#include "network/client-connection.h"
#include "network/host-connection.h"
#include "raylib.h"
#include <memory>

TitleScreen::TitleScreen(const GameState &oldState) : TextScreen { oldState } {}

std::unique_ptr<GameState> TitleScreen::update() {
    if (IsKeyPressed(KEY_H)) {
        m_peerConn = std::make_shared<HostConnection>();
        return std::make_unique<LoadingScreen>(*this);
    }
    if (IsKeyPressed(KEY_J)) {
        m_peerConn = std::make_shared<ClientConnection>();
        return std::make_unique<LoadingScreen>(*this);
    }
    return nullptr;
}

void TitleScreen::render() {
    int titleWidth { MeasureText(s_gameTitle, s_titleFontSize) };
    int subtitleWidth { MeasureText(s_gameSubtitle, s_subtitleFontSize) };
    DrawText(s_gameTitle, (GetScreenWidth() - titleWidth) / 2,
             GetScreenHeight() / 3, s_titleFontSize, WHITE);
    DrawText(s_gameSubtitle, (GetScreenWidth() - subtitleWidth) / 2,
             2 * GetScreenHeight() / 3, s_subtitleFontSize, WHITE);
}
