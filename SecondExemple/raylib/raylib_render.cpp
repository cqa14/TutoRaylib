#include "raylib_render.h"

RaylibRender::RaylibRender() {
    InitWindow(800, 600, "Un cube");

    camera.position = (Vector3){ 5.0f, 5.0f, 5.0f };
    camera.target = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);
}

RaylibRender::~RaylibRender() {
    CloseWindow();
}

void RaylibRender::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawGrid(200, 0.5f);

                c.dessine_sur(*this);
            EndMode3D();

        EndDrawing();
    }
}

void RaylibRender::dessine(Contenu const& a_dessiner) {
    constexpr Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
    DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, LIME);
    DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, DARKGREEN);
}