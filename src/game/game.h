#pragma once

#include "game-state.h"
#include "laser.h"
#include "spaceship.h"
#include <memory>
#include <vector>

class Game : public GameState {
  private:
    Spaceship m_player;
    std::vector<Laser> m_outgoingLasers;

  public:
    Game();
    Game(const GameState &);
    std::unique_ptr<GameState> update() override;
    void render() override;
};
