#include "laser.h"
#include "raylib.h"
#include "spaceship.h"
#include <optional>
#include <vector>

const char *const title = "Space Shootout";
const auto screenWidth = 960;
const auto screenHeight = 720;
const auto fps = 60;

int main() {
    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(fps);
    HideCursor();

    auto player = Spaceship{GetScreenWidth() / 2, GetScreenHeight() / 2};
    std::vector<Laser> lasers{};
    auto laser = Laser{GetScreenWidth() / 2, GetScreenHeight() / 2};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        player.move();
        player.draw();
        laser.move();
        laser.draw();
        std::optional<Laser> shot{player.blast()};
        if (shot) {
            lasers.push_back(*shot);
        }
        for (auto &laser : lasers) {
            laser.move();
            laser.draw();
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
