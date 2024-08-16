#pragma once

#include "text-screen.h"
#include <memory>

class LoadingScreen : public TextScreen {
  private:
    static constexpr auto s_loadingText { "Searching for Opponent..." };

  public:
    LoadingScreen();
    std::unique_ptr<GameState> update() override;
};
