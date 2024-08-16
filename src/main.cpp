#include "raylib.h"
#include "state-machine.h"

const auto g_title { "Space Shootout" };
const auto g_screenWidth { 960 };
const auto g_screenHeight { 720 };
const auto g_fps { 60 };

int main() {
    InitWindow(g_screenWidth, g_screenHeight, g_title);
    SetTargetFPS(g_fps);
    HideCursor();

    StateMachine gameStateMachine {};
    gameStateMachine.runGameLoop();

    CloseWindow();
    return 0;
}
