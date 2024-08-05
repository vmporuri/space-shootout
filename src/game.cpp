#include "game.h"
#include "laser.h"
#include "raylib.h"
#include "spaceship.h"
#include <optional>
#include <vector>

Game::Game() : m_player { GetScreenWidth() / 2, GetScreenHeight() / 2 } {}

void Game::updateOneTick() {
    m_player.move();
    std::optional<Laser> blast { m_player.blast() };
    if (blast) {
        m_outgoingLasers.push_back(*blast);
    }
    m_player.draw();
    for (auto &laser : m_outgoingLasers) {
        laser.move();
        laser.draw();
    }
}
