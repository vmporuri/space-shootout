#include "spaceship.h"
#include "raylib.h"
#include <algorithm>

Spaceship::Spaceship(int posX, int posY) : m_posX{posX}, m_posY{posY} {}

void Spaceship::draw() const {
    DrawRectangle(m_posX, m_posY, sizeX, sizeY, WHITE);
}

void Spaceship::move() {
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        m_posY = std::max(m_posY - speedY, 0);
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        m_posY = std::min(m_posY + speedY, GetScreenHeight() - sizeY);
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        m_posX = std::max(m_posX - speedX, 0);
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        m_posX = std::min(m_posX + speedX, GetScreenWidth() - sizeX);
    }
}
