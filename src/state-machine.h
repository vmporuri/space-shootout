#pragma once

#include "game-state.h"
#include <unordered_map>

class StateMachine {
  private:
    GameState::State m_currState {};
    std::unordered_map<GameState::State, std::unique_ptr<GameState>>
        m_gameStates;

  public:
    StateMachine();
    void changeState(GameState::State newState);
    GameState::State update();
    void render();
};
