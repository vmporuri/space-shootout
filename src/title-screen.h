#pragma once

#include "game-state.h"

const auto g_gameTitle { "Space Shootout" };
const auto g_gameSubtitle { "Press Space to Start" };
const auto g_titleFontSize { 80 };
const auto g_subtitleFontSize { 40 };

class TitleScreen : public GameState {
  private:
    State m_stateType { TITLE_SCREEN };

  public:
    State update() override;
    void render() override;
};
