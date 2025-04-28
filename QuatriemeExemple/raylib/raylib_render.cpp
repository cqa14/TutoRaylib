#include "raylib_render.h"
#include <string>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#undef RAYGUI_IMPLEMENTATION

RaylibRender::RaylibRender() {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(800, 600, "Interactions");

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
        // Si on appuie sur `L`, on active ou désactive le mouvement de la caméra.
        if (IsKeyPressed(KEY_L))
            deplacement = !deplacement;

        // Cela reflète le changement suggéré ci-dessus.
        if (deplacement)
            UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                // On dessine chaque Contenu de la liste.
                for (auto& contenu : liste_contenus) {
                    contenu.dessine_sur(*this);
                }
            EndMode3D();

            /*
             * On peut toujours dessiner par dessus le mode 3D en 2D, il suffit de l'écrire
             * hors du BeginMode3D et EndMode3D.
             */
            DrawText("Appuyez sur 'L' pour activer/désactiver le mouvement de la caméra", 10, 10, 20, DARKGRAY);
            DrawText((std::string("Caméra ") + (deplacement ? "libre" : "fixe")).c_str(), 10, 40, 20, DARKGRAY);

            /*
             * Nous utilisons un toggle pour activer ou désactiver le pointeur.
             * C'est un composant venant de raygui.
             */
            GuiToggle(Rectangle(10, 560, 60, 30), "Pointeur", &pointeur);
            // Si le pointeur est activé, on dessine un cercle à la position de la souris.
            if (pointeur) {
                auto [x, y] = GetMousePosition();
                DrawCircle(static_cast<int>(x), static_cast<int>(y), 10.0f, RED);
            }
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