#pragma once

#include "laser.h"
#include "spaceship.h"
#include <vector>

class Game {
  private:
    Spaceship m_player;
    std::vector<Laser> m_outgoingLasers;

  public:
    Game();
    void updateOneTick();
};
