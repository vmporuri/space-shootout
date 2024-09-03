#pragma once

#include "raylib.h"

class Laser {
  public:
    enum LaserDirection { UP = -1, DOWN = 1 };

  private:
    static constexpr auto s_laserWidth { 8 };
    static constexpr auto s_laserHeight { 30 };
    static constexpr auto s_laserSpeedY { 30 };

    int m_posX;
    int m_posY;
    LaserDirection m_dir;

  public:
    Laser(int posX, int posY, LaserDirection dir = UP);
    [[nodiscard]] int getX() const;
    [[nodiscard]] int getY() const;
    [[nodiscard]] Rectangle getRectangle() const;
    void draw() const;
    void move();
    [[nodiscard]] bool isOffScreen() const;
};
