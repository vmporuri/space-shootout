#include "spaceship.h"
#include "laser.h"
#include "raylib.h"
#include <algorithm>
#include <optional>

Spaceship::Spaceship(int posX, int posY) : m_posX { posX }, m_posY { posY } {}

void Spaceship::draw() const {
    DrawRectangle(m_posX, m_posY, shipWidth, shipHeight, WHITE);
}

void Spaceship::move() {
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        m_posY = std::max(m_posY - shipSpeedY, 0);
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        m_posY = std::min(m_posY + shipSpeedY, GetScreenHeight() - shipHeight);
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        m_posX = std::max(m_posX - shipSpeedX, 0);
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        m_posX = std::min(m_posX + shipSpeedX, GetScreenWidth() - shipWidth);
    }
}

[[nodiscard]] std::optional<Laser> Spaceship::blast() const {
    if (IsKeyPressed(KEY_SPACE)) {
        return Laser { m_posX + shipWidth / 2, m_posY + shipHeight / 2 };
    }
    return std::nullopt;
}
