#pragma once
#include "laser.h"
#include <optional>

const auto shipWidth { 60 };
const auto shipHeight { 60 };
const auto shipSpeedX { 10 };
const auto shipSpeedY { 10 };

class Spaceship {
  private:
    int m_posX;
    int m_posY;

  public:
    Spaceship(int posX, int posY);
    void draw() const;
    void move();
    [[nodiscard]] std::optional<Laser> blast() const;
};
