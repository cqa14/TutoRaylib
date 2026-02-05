#include <raylib.h>


int main()
{
    /*
     * Définition de la largeur et de la hauteur de la fenêtre
     * peut être également passé en paramètre de la fonction InitWindow
     */
    int largeur = 800;
    int hauteur = 450;

    // ###########################################################
    /*
     * Optionnel, les "flags" permettent de définir le comportement de la fenêtre
     * par exemple le redimensionnement "FLAG_WINDOW_RESIZABLE" ou
     * l'adaptation à la résolution "FLAG_WINDOW_HIGHDPI"
     *
     * Voir l'exemple de Raylib pour plus d'informations :
     * https://www.raylib.com/examples/core/loader.html?name=core_window_flags
     */
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
    // ###########################################################

    // Initialisation de la fenêtre, avec la largeur, la hauteur et le titre
    InitWindow(largeur, hauteur, "Premier exemple");

    // Optionnel, on peut fixer une taille minimale pour la fenêtre
    SetWindowMinSize(360, 320);

    //  Optionnel, on peut fixer le nombre d'images par seconde
    SetTargetFPS(60);

    //Boucle principale
    while (!WindowShouldClose())
    {
        /*
         * Récupération de la largeur et de la hauteur de la fenêtre
         * en cas de redimensionnement
         */
        largeur = GetScreenWidth();
        hauteur = GetScreenHeight();

        // Début du dessin
        BeginDrawing();

            // Efface l'écran avec la couleur passée en paramètre
            ClearBackground(RAYWHITE);

            /*
             * On peut placer un texte avec une position fixée
             * Les paramètres sont :
             * - le texte
             * - la position x
             * - la position y
             * - la taille de la police
             * - la couleur
             */
            DrawText("Ceci est un cercle", 20, 20, 20, DARKGRAY);

            /*
             * On peut également dessiner des formes géométriques
             * par exemple un cercle, dont le centre est à la moitié de la largeur et de la hauteur
             * de la fenêtre, un rayon de 100 et une couleur rouge
             */
            DrawCircle(largeur / 2, hauteur / 2, 100, RED);

        EndDrawing();
    }

    // Fermeture de la fenêtre
    CloseWindow();
    return 0;
}
