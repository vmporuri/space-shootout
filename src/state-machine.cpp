#include "state-machine.h"
#include "game-state.h"
#include "title-screen.h"
#include <memory>

StateMachine::StateMachine()
    : m_currState { std::make_unique<TitleScreen>() } {}

void StateMachine::runGameLoop() {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        std::unique_ptr<GameState> newState { update() };
        render();
        changeState(std::move(newState));

        EndDrawing();
    }
}

void StateMachine::changeState(std::unique_ptr<GameState> newState) {
    if (newState) {
        m_currState = std::move(newState);
    }
}

std::unique_ptr<GameState> StateMachine::update() {
    return m_currState->update();
}

void StateMachine::render() { return m_currState->render(); }
