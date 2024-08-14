#pragma once

#include "game-state.h"

const auto g_loadingText { "Searching for Opponent..." };
const auto g_loadingFontSize { 40 };

class LoadingScreen : public GameState {
  private:
    State m_stateType { LOADING_SCREEN };

  public:
    State update() override;
    void render() override;
};
