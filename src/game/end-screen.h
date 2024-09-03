#pragma once

#include "text-screen.h"
#include <memory>

class EndScreen : public TextScreen {
  private:
    static constexpr auto s_victoryText { "You won!" };
    static constexpr auto s_lossText { "You lost." };
    static constexpr auto s_subtitleText {
        "Press Space to Return to the Title Screen."
    };
    static constexpr auto s_titleFontSize { 80 };
    static constexpr auto s_subtitleFontSize { 40 };

    bool m_wonGame {};

  public:
    EndScreen() = default;
    EndScreen(const GameState &);
    std::unique_ptr<GameState> update() override;
    void render() override;
    void setWinStatus(bool wonGame);
};
