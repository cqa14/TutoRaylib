# Tuto Raylib

TODO: cadre/objectif (court)

---

## Installation

TODO (c'est fait par le CMakefile mais expliquer un peu ce que ça cherche où
pour donner la possibilité de comprendre la Note suivante / de s'adapter si nécessaire)

### Notes
Pour compiler sur les VMs de l'EPFL, il suffit de baisser la version dans le `cmake_minimum_required` (une fois pour le projet et l'autre dans Raylib une fois cloné), mais cela compile bien au final.

---

## Premier exemple : prise en main

Commençons par la construction d'une première fenêtre, avec un texte et une figure en deux dimensions. On fait d'abord cela dans un unique fichier, que l'on modularisera par la suite.

Il faut tout d'abord inclure les fichiers d'en-tête de Raylib, et écrivons la fonction `main`.

```c++
#include <raylib.h>


int main() {
    // À compléter
}
```

Pour pouvoir afficher quelque chose, il faut d'abord initialiser la fenêtre. On peut le faire en utilisant la fonction `InitWindow`, qui prend en argument la largeur et la hauteur de la fenêtre, ainsi qu'un titre. Il faut ensuite faire une boucle d'affichage, qui se termine lorsque l'utilisateur ferme la fenêtre. Finalement, il ne faut pas oublier de libérer les ressources utilisées par Raylib via la fonction `CloseWindow`.

```c++
#include <raylib.h>


int main() {
    InitWindow(800, 450, "Premier exemple");

    while (!WindowShouldClose()) {
        BeginDrawing();
               
            // Ce que l'on veut afficher     
              
        EndDrawing();
    }

    CloseWindow();
}
```

On peut maintenant ajouter différents éléments à afficher. Par exemple, on peut afficher un texte en utilisant la fonction `DrawText`, qui prend en argument le texte à afficher, la position du coin supérieur gauche du texte, la taille de la police et la couleur du texte.

Il y a également la possibilité d'afficher des formes géométriques. Par exemple, on peut afficher un cercle via la fonction `DrawCircle`, qui prend en argument le centre du cercle, son rayon, sa couleur et sa bordure.

Il est important en règle générale de remettre la couleur de fond de la fenêtre à chaque frame, pour éviter que les éléments ne se superposent. Celà se fait via la fonction `ClearBackground`, qui prend en argument la couleur desirée.

```c++
#include <raylib.h>


int main() {
    InitWindow(800, 450, "Premier exemple");

    while (!WindowShouldClose()) {
        BeginDrawing();
        
            ClearBackground(RAYWHITE);
               
            DrawText("Ceci est un cercle", 20, 20, 20, DARKGRAY);

            DrawCircle(400, 225, 100, RED);  
                      
        EndDrawing();
    }

    CloseWindow();
}
```

À ce stade, cela devrait ressembler à ceci :

![ex1_img.png](PremierExemple/ex1_img.png)

Avant de passer à la suite, nous mentionnerons encore plusieurs paramètres pouvant être utiles quant au paramétrage de la fenêtre. Par exemple, il y a un système de `flags` qui permettent de définir le comportement de la fenêtre. On peut par exemple définir si la fenêtre est redimensionnable, si elle est en plein écran, si elle est visible, etc. On peut également lui fixer une taille minimale afin que nos éléments ne soient pas trop écrasés. Il est aussi commun de fixer un nombre de frames par seconde, pour éviter que le programme ne tourne trop vite.

```c++
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
InitWindow(800, 450, "Premier exemple");

// Optionnel, on peut fixer une taille minimale pour la fenêtre
SetWindowMinSize(360, 320);

//  Optionnel, on peut fixer le nombre d'images par seconde
SetTargetFPS(60);
```

Finalement, nous allons voir comment centrer le cercle dans la fenêtre lorsqu'elle est redimensionnable. Pour cela, on peut utiliser la fonction `GetScreenWidth` et `GetScreenHeight` pour obtenir la taille de l'écran, et ainsi calculer la position du cercle. Afin d'améliorer la lisibilité du code, on peut également définir deux variables pour la largeur et la hauteur de la fenêtre.

```c++
#include <raylib.h>


int main()
{
    int largeur = 800;
    int hauteur = 450;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
    InitWindow(largeur, hauteur, "Premier exemple");
    SetWindowMinSize(360, 320);

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

            ClearBackground(RAYWHITE);

            DrawText("Ceci est un cercle", 20, 20, 20, DARKGRAY);

            DrawCircle(largeur / 2, hauteur / 2, 100, RED);

        EndDrawing();
    }

    CloseWindow();
}
```

> Pour découvrir d'autres exemples et trouver de l'inspiration, vous pouvez consulter la [galerie d'exemples de Raylib](https://www.raylib.com/examples.html). Il existe également une page regroupant les [différentes fonctions de Raylib](https://www.raylib.com/cheatsheet/cheatsheet.html), mais elle est moins pratique à utiliser.

---

## Deuxième exemple : modularisation et dessin 3D
