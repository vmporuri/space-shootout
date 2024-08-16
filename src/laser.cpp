#include "laser.h"

#include "raylib.h"

Laser::Laser(int posX, int posY) : m_posX { posX }, m_posY { posY } {}

void Laser::draw() const {
    DrawRectangle(m_posX, m_posY, s_laserWidth, s_laserHeight, WHITE);
}

void Laser::move() { m_posY -= s_laserSpeedY; }

[[nodiscard]] bool Laser::isOffScreen() const {
    return m_posY > GetScreenHeight();
}
