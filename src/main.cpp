#include "enet/enet.h"
#include "game/state-machine.h"
#include "raylib.h"

static const auto g_title { "Space Shootout" };
static constexpr auto g_screenWidth { 960 };
static constexpr auto g_screenHeight { 720 };
static constexpr auto g_fps { 60 };

int main() {
    InitWindow(g_screenWidth, g_screenHeight, g_title);
    SetTargetFPS(g_fps);
    HideCursor();

    if (enet_initialize() != 0) {
        std::cerr << "Error initializing ENet library.\n";
        std::exit(EXIT_FAILURE);
    }
    std::atexit(enet_deinitialize);

    StateMachine gameStateMachine {};
    gameStateMachine.runGameLoop();

    CloseWindow();
    return 0;
}
