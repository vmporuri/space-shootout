#pragma once

const auto sizeX = 30;
const auto sizeY = 30;
const auto speedX = 5;
const auto speedY = 5;

class Spaceship {
  private:
    int m_posX;
    int m_posY;

  public:
    Spaceship(int posX, int posY);
    void draw() const;
    void move();
};
