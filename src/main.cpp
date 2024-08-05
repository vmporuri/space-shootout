#include "game.h"
#include "raylib.h"

const auto title { "Space Shootout" };
const auto screenWidth { 960 };
const auto screenHeight { 720 };
const auto fps { 60 };

int main() {
    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(fps);
    HideCursor();

    Game game {};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        game.updateOneTick();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
