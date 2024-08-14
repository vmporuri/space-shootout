#include "state-machine.h"
#include "game-state.h"
#include "game.h"
#include "loading-screen.h"
#include "title-screen.h"
#include <memory>
#include <unordered_map>

StateMachine::StateMachine() : m_currState { GameState::TITLE_SCREEN } {
    m_gameStates.insert_or_assign(GameState::TITLE_SCREEN,
                                  std::make_unique<TitleScreen>());
    m_gameStates.insert_or_assign(GameState::LOADING_SCREEN,
                                  std::make_unique<LoadingScreen>());
    m_gameStates.insert_or_assign(GameState::GAME, std::make_unique<Game>());
}

void StateMachine::changeState(GameState::State newState) {
    m_currState = newState;
}

GameState::State StateMachine::update() {
    return m_gameStates[m_currState]->update();
}

void StateMachine::render() { m_gameStates[m_currState]->render(); }
