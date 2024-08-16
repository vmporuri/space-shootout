#pragma once

class Laser {
  private:
    static constexpr auto s_laserWidth { 8 };
    static constexpr auto s_laserHeight { 30 };
    static constexpr auto s_laserSpeedY { 30 };

    int m_posX;
    int m_posY;

  public:
    Laser(int posX, int posY);
    void draw() const;
    void move();
    [[nodiscard]] bool isOffScreen() const;
};
