#include "raylib_render.h"

RaylibRender::RaylibRender() {
    /*
     * On prépare les initialisations de la fenêtre
     * comme dans le premier exemple.
     */
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(800, 600, "Un cube");

    /*
     * Pour le dessin 3D, on va utiliser une caméra qu'il faut
     * préparer.
     * On doit donc lui donner une position, une cible (le point vers lequel
     * elle regarde) et un vecteur "up" (le haut de l'écran pour la
     * caméra). On lui donne aussi un champ de vision (fovy) et le type de projection
     * (ici perspective).
     */
    camera.position = (Vector3){ 5.0f, 5.0f, 5.0f };
    camera.target = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    SetTargetFPS(60);
}

RaylibRender::~RaylibRender() {
    // On ferme la fenêtre à la destruction de l'objet.
    CloseWindow();
}

void RaylibRender::run() {
    /*
     * Méthode principale de la classe pour dessiner
     * la fenêtre.
     */
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Pour le dessin 3D, il faut commencer par activer le mode 3D.
            BeginMode3D(camera);
                // Afin de bien voir le cube, on va dessiner une grille.
                DrawGrid(200, 0.5f);

                // Et on dessine le contenu.
                c.dessine_sur(*this);
            EndMode3D();
        EndDrawing();
    }
}

void RaylibRender::dessine(Contenu const& a_dessiner) {
    /*
     * On va dessiner un cube, centré sur le point (0, 1, 0).
     * Afin de bien le voir, on va aussi dessiner ses arêtes
     * par la méthode DrawCubeWires.
     */
    constexpr Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
    DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, LIME);
    DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, DARKGREEN);
}