#pragma once

#include "text-screen.h"
#include <memory>

const auto g_gameTitle { "Space Shootout" };
const auto g_gameSubtitle { "Press Space to Start" };
const auto g_titleFontSize { 80 };
const auto g_subtitleFontSize { 40 };

class TitleScreen : public TextScreen {
  public:
    TitleScreen();
    std::unique_ptr<GameState> update() override;
    void render() override;
};
