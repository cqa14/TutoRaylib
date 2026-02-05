#include "raylib_render.h"

RaylibRender::RaylibRender() {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(800, 600, "Un singe");

    camera.position = { 0.0f, 2.0f, 5.0f };
    camera.target = { 0.0f, 1.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // On doit d'abord importer le modèle
    myModel = LoadModel(TextFormat("%sresources/monkey.glb", GetApplicationDirectory()));

    SetTargetFPS(60);
}

RaylibRender::~RaylibRender() {
    // On doit libérer le modèle avant de fermer la fenêtre
    UnloadModel(myModel);
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
    constexpr Vector3 modelPosition = { 0.0f, 1.0f, 0.0f };
    // Cela se dessine similairement au cube
    DrawModel(myModel, modelPosition, 1.0f, WHITE);
}
