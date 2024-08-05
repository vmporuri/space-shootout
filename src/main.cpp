#include "laser.h"
#include "raylib.h"
#include "spaceship.h"

const char *const title = "Space Shootout";
const auto screenWidth = 960;
const auto screenHeight = 720;
const auto fps = 60;

int main() {
    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(fps);
    HideCursor();

    auto player = Spaceship{GetScreenWidth() / 2, GetScreenHeight() / 2};
    auto laser = Laser{GetScreenWidth() / 2, GetScreenHeight() / 2};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        player.move();
        player.draw();
        laser.move();
        laser.draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
