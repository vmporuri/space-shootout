#pragma once

#include "text-screen.h"
#include <memory>

class TitleScreen : public TextScreen {
  private:
    static constexpr auto s_gameTitle { "Space Shootout" };
    static constexpr auto s_gameSubtitle {
        "Press [ H ] to Host or [ J ] to Join"
    };
    static constexpr auto s_titleFontSize { 80 };
    static constexpr auto s_subtitleFontSize { 40 };

  public:
    TitleScreen() = default;
    TitleScreen(const GameState &);
    std::unique_ptr<GameState> update() override;
    void render() override;
};
