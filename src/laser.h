#pragma once

const auto laserWidth = 8;
const auto laserHeight = 30;
const auto laserSpeedY = 30;

class Laser {
  private:
    int m_posX;
    int m_posY;

  public:
    Laser(int posX, int posY);
    void draw() const;
    void move();
    [[nodiscard]] bool isOffScreen() const;
};
