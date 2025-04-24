#include "raylib_render.h"

RaylibRender::RaylibRender() {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(800, 600, "Des cubes");

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

                for (auto& contenu : liste_contenus) {
                    contenu.dessine_sur(*this);
                }

            EndMode3D();
        EndDrawing();
    }
}

void RaylibRender::dessine(Contenu const& a_dessiner) {
    const auto [x, y, z] = a_dessiner.get_position();
    const Vector3 cubePosition = { static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) };
    auto color = WHITE;
    switch (a_dessiner.get_color()) {
        case ROUGE:
            color = RED;
            break;
        case VERT:
            color = GREEN;
            break;
        case BLEU:
            color = BLUE;
            break;
        default:
            break;
    }
    DrawCube(cubePosition, 1.0f, 1.0f, 1.0f, color);
    DrawCubeWires(cubePosition, 1.0f, 1.0f, 1.0f, BLACK);
}