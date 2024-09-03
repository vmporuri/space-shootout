#include "laser.h"

#include "raylib.h"

Laser::Laser(int posX, int posY, LaserDirection dir)
    : m_posX { posX }, m_posY { posY }, m_dir { dir } {}

[[nodiscard]] int Laser::getX() const { return m_posX; }

[[nodiscard]] int Laser::getY() const { return m_posY; }

[[nodiscard]] Rectangle Laser::getRectangle() const {
    return { static_cast<float>(m_posX), static_cast<float>(m_posY),
             s_laserWidth, s_laserHeight };
}

void Laser::draw() const {
    DrawRectangle(m_posX, m_posY, s_laserWidth, s_laserHeight, WHITE);
}

void Laser::move() { m_posY += m_dir * s_laserSpeedY; }

[[nodiscard]] bool Laser::isOffScreen() const {
    return m_posY < 0 || m_posY > GetScreenHeight();
}
