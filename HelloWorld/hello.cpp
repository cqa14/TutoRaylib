#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION

int main() {
    // Initialization
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Hello World Example");

    bool showMessage = false;
    double messageStartTime = 0;

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        if (GuiButton((Rectangle){ 350, 200, 100, 50 }, "Press Me")) {
            showMessage = true;
            messageStartTime = GetTime();
        }

        if (showMessage && (GetTime() - messageStartTime > 3.0)) {
            showMessage = false;
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (showMessage) {
            DrawText("Hello World", 350, 100, 20, DARKGRAY);
        }

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}
