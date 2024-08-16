#include "raylib.h"
#include "state-machine.h"

const auto title { "Space Shootout" };
const auto screenWidth { 960 };
const auto screenHeight { 720 };
const auto fps { 60 };

int main() {
    InitWindow(screenWidth, screenHeight, title);
    SetTargetFPS(fps);
    HideCursor();

    StateMachine gameStateMachine {};
    gameStateMachine.runGameLoop();

    CloseWindow();
    return 0;
}
