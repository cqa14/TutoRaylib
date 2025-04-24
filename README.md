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

On va maintenant modulariser notre code. Le but ici est de séparer ce que l'on veut visualiser et le contenu de celui-ci. L'idée est d'organiser le programme selon deux grand principe (dit "[design patterns](https://fr.wikipedia.org/wiki/Patron_de_conception)") :

- Clairement séparer trois choses : la gestion de l'application (le `main` ou le `run`, cf. plus loin), le contenu à afficher et la façon de l'afficher (dans les différentes formes : affichage à l'écran, texte, dans un fichier, ...).
- Et il en suit une claire distinction entre ce qui doit être affiché, et la manière de le faire sur les différents supports, celle-ci ne devant pas intérferer avec le contenu.

> Dans ce qui suit, nous détaillons la démarche, mais il n'est pas nécessaire de tout comprendre dans le détail pour pouvoir bien réutiliser le code fourni. Néanmoins, une fois les connaissances nécessaires à la compréhension de celui-ci acquise, il peut toujours être intéressant de revenir sur les différents choix de conception.

Nous allons séparer le code sur trois grands axes (libre au lecteur d'adapter cela à ses besoins), dans trois répertoires :

### Général

D'un point de vue abstrait, nous différencierons ce qui est dessinable et les supports à dessein, comme dit en préambule. Conceptuellement, le dessinable est le plus simple, il lui suffit d'avoir une méthode permettant de le dessiner sur un support.

```c++
#pragma once

class SupportADessin;

class Dessinable {
public:
    virtual void dessine_sur(SupportADessin&) = 0;

    // Mise par défaut des constructeurs, ...
    virtual ~Dessinable() = default;
    Dessinable(Dessinable const&) = default;
    Dessinable& operator=(Dessinable const&) = default;
    Dessinable(Dessinable&&) = default;
    Dessinable& operator=(Dessinable&&) = default;

    Dessinable() = default;
};
```

Le support fournit quant à lui une méthode pour dessiner les différents contenus.

```c++
#pragma once

class Contenu;

class SupportADessin {
public:
    virtual ~SupportADessin() = default;
    // On ne copie pas les Supports.
    SupportADessin(SupportADessin const&) = delete;
    SupportADessin& operator=(SupportADessin const&) = delete;
    // Mais on peut les déplacer.
    SupportADessin(SupportADessin&&) = default;
    SupportADessin& operator=(SupportADessin&&) = default;

    SupportADessin() = default;

    virtual void dessine(Contenu const& a_dessiner) = 0;

    /*
     * Mettre ici toutes les méthodes nécessaires pour dessiner tous les
     * objets que l'on veut dessiner. Par exemple :
     */
    // virtual void dessine(Nounours const& a_dessiner) = 0;
    // virtual void dessine(Voiture const& a_dessiner) = 0;
};
```

Maintenant, pour notre contenu, il suffit de dériver de la classe `Dessinable` et de redéfinir la méthode `dessine_sur` comme suit :

```c++
#pragma once

#include "dessinable.h"
#include "support_a_dessin.h"

class Contenu : public Dessinable {
public:
    /*
     * Le reste de la classe peut être quelconque selon les besoins.
     */
    ~Contenu() override = default;
    Contenu(Contenu const&) = default;
    Contenu& operator=(Contenu const&) = default;
    Contenu(Contenu&&) = default;
    Contenu& operator=(Contenu&&) = default;

    Contenu() = default;

    /*
     * Ceci est la méthode devant être ajoutée à toute classe
     * étendant Dessinable, afin de pouvoir être dessinée.
     */
    void dessine_sur(SupportADessin& support) override
    { support.dessine(*this); }
};
```

`dessine_sur` fait alors exactement ce que son nom indique, elle va appeler la méthode `dessine` du support, en lui passant le contenu à dessiner. 

> Le fait de devoir copier cette définition de `dessine_sur`, qui est la même pour chaque `Dessinable`, peut paraitre contre intuitif (en effet, pourquoi ne pas juste la mettre dans dessinable ?). Cela est entre autre dû au fait que cette architecture, appelée "[double dispatch](https://en.wikipedia.org/wiki/Double_dispatch)", est une généralisation du polymorphisme qui n'est pas totalement prévue en C++.

### Texte

Passons donc à l'utilisation de cette nouvelle abstraction pour visualiser notre contenu en mode texte, avec un `main` ressemblant à cela :

```c++
#include <iostream>
#include "text_viewer.h"
#include "contenu.h"

int main()
{
  TextViewer ecran(std::cout);

  Contenu c;
  c.dessine_sur(ecran);

  return 0;
}
```

Le `TextViewer` est un support qui va afficher le contenu sur la sortie standard.

```c++
#pragma once

#include <iostream>
#include "support_a_dessin.h"

class TextViewer : public SupportADessin {
public:
    explicit TextViewer(std::ostream& flot) : flot(flot) {}

    ~TextViewer() override = default;
    TextViewer(TextViewer const&) = delete;
    TextViewer& operator=(TextViewer const&) = delete;
    TextViewer(TextViewer&&) = default;
    TextViewer& operator=(TextViewer&&) = default;

    /*
     * Il faut surcharger la méthode dessine pour dessiner le contenu.
     * Ne pas oublier de le faire pour toutes les méthodes de dessin !
     */
    void dessine(Contenu const& a_dessiner) override;

private:
    std::ostream& flot;
};
```

On peut alors implémenter la méthode `dessine` pour afficher le contenu sur la sortie standard.

```c++
#include <iostream>
#include "text_viewer.h"
#include "contenu.h"

void TextViewer::dessine(Contenu const&)
{
    flot <<
        "+------+.   " << std::endl <<
        "|`.    | `. " << std::endl <<
        "|  `+--+---+" << std::endl <<
        "|   |  |   |" << std::endl <<
        "+---+--+.  |" << std::endl <<
        " `. |    `.|" << std::endl <<
        "   `+------+" << std::endl;
    // Dessin de https://www.asciiart.eu/art-and-design/geometries
}
```

Bien entendu que dans un cas concret, nous utiliserons le contenu en paramètre afin d'afficher quelque chose de pertinent ! Maintenant, si l'on compile et exécute le `main` fournit au début, on a bien dans le terminal :

```
+------+.
|`.    | `.
|  `+--+---+
|   |  |   |
+---+--+.  |
 `. |    `.|
   `+------+
```

### Raylib

Pour l'affichage graphique, nous procéderons un peu différemment, et notre `main` ressemblera à ceci :

```c++
#include "raylib_render.h"

int main()
{
    RaylibRender ecran;
    ecran.run();
}
```

Ici, nous appelons la méthode `dessine_sur` dans la méthode `run`, et nous avons le contenu qui sera un attribut de la classe `RaylibRender`.

```c++
#pragma once

#include "support_a_dessin.h"
#include "contenu.h"
#include <raylib.h>

class RaylibRender final : public SupportADessin {
public:
    RaylibRender();
    ~RaylibRender() override;

    void run();

    void dessine(Contenu const& a_dessiner) override;
private:
    Camera3D camera = { 0 };
    
    Contenu c;
};
```

> Notons que le contenu pourrait être remplacé par un pointeur vers un contenu pour éviter des copies.

Dans cette partie, nous aborderons aussi le dessin 3D, d'où la caméra mise en attribut de cette classe. Nous allons maintenant préparer les constructeurs et destructeurs afin que nous n'ayons qu'à nous soucier de l'affichage dans la méthode `run`.

```c++
RaylibRender::RaylibRender() {
    // parmétres de la fenêtre
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(800, 600, "Un cube");

    // paramétres de la caméra
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
```

On notera donc que l'initialisation et la fermeture de la fenêtre sont identiques, mais on y rajoute des paramètres de caméra, comme sa position, le point qu'elle vise (`target`), le vecteur représentant la direction "haut" pour elle (`up`), son champ de vision (`fovy`) et le type de projection.

On peut maintenant faire notre fonction `run` afin d'avoir un affichage fonctionnel.

```c++
void RaylibRender::run() {
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                // Afin de bien voir le cube, on va dessiner une grille.
                DrawGrid(200, 0.5f);

                // Et on dessine le contenu.
                c.dessine_sur(*this);
            EndMode3D();
        EndDrawing();
    }
}
```

Comme dans le premier exemple, on a notre boucle d'exécution où l'on remet un fond blanc avant de dessiner. Néanmoins, nous devons maintenant entrer dans un mode 3D, avec notre caméra en argument, afin de dessiner nos objets. Il ne manque plus qu'à savoir dessiner le contenu, et cela se fait par la méthode dessine.

```c++
void RaylibRender::dessine(Contenu const& a_dessiner) {
    Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
    DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, LIME);
    DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, DARKGREEN);
}
```

Le dessin d'un cube se fait alors en appelant la fonction `DrawCube` avec en argument la position de celui-ci, sa largeur, sa hauteur, sa profondeur et sa couleur.

> Notons que les fonctions de Raylib, ayant à la base été faite en C, ne prennent pas en paramètre des `vector` de C++, mais des `Vector2` / `Vector3` de Raylib, selon le nombre de composantes. Similairement, les arguments sont prévus en `float` et non en double, et certaines erreurs peuvent venir de là et sont donc réglables en forçant la conversion en float.

Nous obtenons alors un affichage 3D, qui ressemble à ceci :

![ex2_img.png](SecondExemple/ex2_img.png)

Dans les codes ci-dessus, nous utilisons également les fonctions `DrawCubeWires` et `DrawGrid`, qui permettent respectivement de dessiner les contours du cube et une grille au sol afin de mettre en évidence les objets, mais ceci est superflus en soi.

> Les objets peuvent paraitre très plat, car il n'y a pas de système de lumière par défaut, ni de méthode suffisamment simple pour le présenter ici, ce qui fait qu'il n'y a pas d'ombres par exemple.

![ex2_img2.png](SecondExemple/ex2_img2.png)


































