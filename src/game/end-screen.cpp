#include "end-screen.h"
#include "game-state.h"
#include "game/title-screen.h"
#include "raylib.h"
#include "text-screen.h"
#include <memory>

EndScreen::EndScreen(const GameState &oldState) : TextScreen { oldState } {}

void EndScreen::setWinStatus(bool wonGame) { m_wonGame = wonGame; }

std::unique_ptr<GameState> EndScreen::update() {
    if (IsKeyPressed(KEY_SPACE)) {
        m_peerConn->disconnectPeer();
        return std::make_unique<TitleScreen>(*this);
    }
    return nullptr;
}

void EndScreen::render() {
    const char *endText {};
    if (m_wonGame) {
        endText = s_victoryText;
    } else {
        endText = s_lossText;
    }
    int titleWidth { MeasureText(endText, s_titleFontSize) };
    int subtitleWidth { MeasureText(s_subtitleText, s_subtitleFontSize) };
    DrawText(endText, (GetScreenWidth() - titleWidth) / 2,
             GetScreenHeight() / 3, s_titleFontSize, WHITE);
    DrawText(s_subtitleText, (GetScreenWidth() - subtitleWidth) / 2,
             2 * GetScreenHeight() / 3, s_subtitleFontSize, WHITE);
}
