#include "game.h"
#include "game-state.h"
#include "laser.h"
#include "raylib.h"
#include "spaceship.h"
#include <memory>
#include <optional>
#include <vector>

Game::Game() : m_player { GetScreenWidth() / 2, GetScreenHeight() / 2 } {}

std::unique_ptr<GameState> Game::update() {
    m_player.move();
    std::optional<Laser> blast { m_player.blast() };
    if (blast) {
        m_outgoingLasers.push_back(*blast);
    }
    return std::unique_ptr<GameState> {};
}

void Game::render() {
    m_player.draw();
    for (auto &laser : m_outgoingLasers) {
        laser.move();
        laser.draw();
    }
}
