#pragma once

#include "game-state.h"
#include "laser.h"
#include "spaceship.h"
#include <vector>

class Game : public GameState {
  private:
    Spaceship m_player;
    std::vector<Laser> m_outgoingLasers;
    State m_stateType { GAME };

  public:
    Game();
    State update() override;
    void render() override;
};
