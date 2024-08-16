#pragma once

#include "text-screen.h"
#include <memory>

const auto g_loadingText { "Searching for Opponent..." };

class LoadingScreen : public TextScreen {
  public:
    LoadingScreen();
    std::unique_ptr<GameState> update() override;
};
