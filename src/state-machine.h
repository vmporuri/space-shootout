#pragma once

#include "game-state.h"

class StateMachine {
  private:
    std::unique_ptr<GameState> m_currState;

  public:
    StateMachine();
    void runGameLoop();
    void changeState(std::unique_ptr<GameState> newState);
    std::unique_ptr<GameState> update();
    void render();
};
