#include "raylib_render.h"
#include <rlgl.h>

RaylibRender::RaylibRender() {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(800, 600, "Toupie");

    camera.position = { 5.0f, 5.0f, 5.0f };
    camera.target = { 0.0f, 1.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);
}

RaylibRender::~RaylibRender() {
    CloseWindow();
}

bool RaylibRender::should_close() const {
    return WindowShouldClose();
}

double RaylibRender::frame_time() const {
    return GetFrameTime();
}

void RaylibRender::begin_frame() {
    BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
            DrawGrid(200, 0.5f);
}

void RaylibRender::end_frame() {
        EndMode3D();
    EndDrawing();
}

void RaylibRender::dessine(Contenu const& a_dessiner) {
    constexpr Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
    /*
     *  Pour faire pivoter le cube, on utilise les outils de rlgl
     *  afin d'appliquer une transformation à notre scène
     *
     *  Dans que on ne met par rlPopMatrix, toutes les transformations
     *  que l'on applique sont faites
     */
    rlPushMatrix();
    // On y fait une rotation autour de l'axe Y
    rlRotatef(static_cast<float>(a_dessiner.get_angle()), 0.0f, 1.0f, 0.0f);

    // On dessine ce qui doit être ainsi transformé
    DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, LIME);
    DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, DARKGREEN);

    // Et on enlève la transformation
    rlPopMatrix();
}
