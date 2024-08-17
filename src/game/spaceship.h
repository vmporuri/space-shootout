#pragma once

#include "laser.h"
#include <optional>

class Spaceship {
  private:
    static constexpr const auto s_shipWidth { 60 };
    static constexpr const auto s_shipHeight { 60 };
    static constexpr const auto s_shipSpeedX { 10 };
    static constexpr const auto s_shipSpeedY { 10 };

    int m_posX;
    int m_posY;

  public:
    Spaceship(int posX, int posY);
    void draw() const;
    void move();
    [[nodiscard]] std::optional<Laser> blast() const;
};
