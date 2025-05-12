# Tuto Raylib

> Il existe de nombreuses autres bibliothèques permettant de créer des interfaces graphiques, comme [Qt](https://qt.io/), [GLFW](https://www.glfw.org/), [OGRE](https://www.ogre3d.org/), [wxWidgets](https://www.wxwidgets.org/), ou encore [SDL](https://www.libsdl.org/), qui ont chacunes leurs avantages et inconvénients, donc il ne faut surtout pas hésiter à regarder s'il y en a une semblant plus adaptée à un projet particulier.

## Introduction

Dans la vie courante, il est rare d'intéragir avec un programme directement par le terminal. Les interfaces graphiques offrent de nouvelles possibilités d'affichage ainsi qu'une expérience utilisateur plus agréable. Ce document vise à donner un aperçu de Raylib, une bibliothèque permettant de créer des interfaces graphiques en C++.

> [Raylib](https://www.raylib.com) est à l'origine une bibliothèque C, pensée pour programmer des jeux vidéo à l'origine. Elle a l'avantage d'être relativement simple à utiliser, et d'avoir été portée dans de nombreux langages et sur toutes les plateformes. Son origine du C fait que certains exemples de la documentation doivent être quelque peu adaptés pour être dans un style plus proche du C++.

Le document structuré comme suit :

1. Nous verrons un [exemple simple de création d'une fenêtre](#premier-exemple--prise-en-main), avec un texte et une figure en 2D.
2. Nous modulariserons le code afin de séparer le contenu à afficher et la manière de l'afficher, et présenterons du même coup un [exemple de dessin 3D](#deuxième-exemple--modularisation-et-dessin-3d).
3. On complexifiera un peu l'affichage en [ajoutant plusieurs objets](#troisième-exemple--dessin-de-plusieurs-objets-et-mouvements-de-caméra), ainsi que la possibilité de déplacer la caméra.
4. Le [quatrième exemple](#quatrième-exemple--interactivité-souris-clavier-boutons-) montrera comment rendre l'affichage interactif, avec la souris et le clavier, ainsi que des boutons.
5. Le [cinquième exemple](#cinquième-exemple--évolution-en-temps-réel) montrera comment faire évoluer le dessin en fonction du temps.
6. Finalement, le [dernier exemple](#sixième-exemple--ajout-dobjets-plus-complexes) montrera comment afficher un modèle 3D plus complexe.

### Quelques concepts préalables

Quand on utilise une bibliothèque graphique, il faut bien comprendre son comportement. Il y a celles qui utilisent une approche de dessin séquentielle, donc on dessine un objet, puis un autre, et ainsi de suite, et il y a celle évènementielle, dont Raylib fait partie. L'idée est que l'on va avoir une boucle infinie qui va attendre un évènement, et lorsque celui-ci se produit, on va le traiter. Cela peut être un clic de souris, une touche de clavier ou même un certain temps d'attente.

Il faut donc programmer avant cette boucle toutes les fonctions qui vont être associées à ces évènements, puis initialiser tout ce qu'il faut (fenêtres de dessin, boutons, variables, ...) avant de lancer la boucle.

En général, on structure celle-ci de la manière suivante :

1. Gestion des évènements,
2. Évolution du système (évènements liés au temps, donc on peut le voir comme un cas particulier du 1.),
3. Dessin de la nouvelle image.

Ce sont ces étapes qui seront détaillées dans la suite de ce document.

---

## Installation et compilation

Afin de faciliter l'usage de Raylib, nous allons utiliser [CMake](https://cmake.org/), mais l'usage d'un MAKEFILE est également possible si Raylib est disponible sur le système, en ajoutant le flag `-lraylib`. Nous laisserons le soin au lecteur de regarder comment faire l'installation si cela l'intéresse ([référence d'installation sur le GitHub de Raylib](https://github.com/raysan5/raylib?tab=readme-ov-file#build-and-installation)).

Avec CMake, on pourra directement installer Raylib pour le projet, ce qui permet de ne pas avoir à s'en soucier sur chaque appareil sur lequel on sera amené à travailler. Pour commencer, il faut créer un fichier `CMakeLists.txt` à la racine du projet, qui contiendra les instructions de construction pour les différents exécutables. On commence par indiquer la version minimale de CMake requise, ainsi que la version de C++ à utiliser. On peut également indiquer le nom du projet et sa version.

```cmake 
# CMakeLists.txt
cmake_minimum_required(VERSION 3.21)
project(NOM_DU_PROJET)
set(CMAKE_CXX_STANDARD 20)
```

Ensuite, on peut ajouter les instructions pour vérifier si Raylib est installé sur le système, et s'il ne l'est pas, de l'installer. Si l'on désire avoir accès à des boutons, on peut également ajouter l'installation de [Raygui](https://github.com/raysan5/raygui) (une autre option pour Raygui est de copier le [header](https://github.com/raysan5/raygui/blob/master/src/raygui.h) dans le projet et de le traiter comme un header classique).

```cmake
# CMakeLists.txt
# ...
# Inspiré de https://github.com/raysan5/raylib/blob/master/projects/CMake/CMakeLists.txt
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        FetchContent_MakeAvailable(raylib)
    endif ()
endif ()

# Optionnel : installation de raygui
FetchContent_Declare(
        raygui
        GIT_REPOSITORY "https://github.com/raysan5/raygui.git"
        GIT_TAG "4.0"
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raygui)
```

Considérons une structure de projet comme suit :

```
.
├── CMakeLists.txt
├── build
├── QuatriemeExemple
│   ├── CMakeLists.txt
│   ├── general
│   │   ├── CMakeLists.txt
│   │   ├── contenu.h
│   │   ├── dessinable.h
│   │   └── support_a_dessin.h
│   └── raylib
│       ├── CMakeLists.txt
│       ├── main_raylib.cpp
│       ├── raylib_render.cpp
│       └── raylib_render.h
└── SecondExemple
    ├── CMakeLists.txt
    ├── general
    │   ├── CMakeLists.txt
    │   ├── contenu.h
    │   ├── dessinable.h
    │   └── support_a_dessin.h
    ├── raylib
    │   ├── CMakeLists.txt
    │   ├── main_raylib.cpp
    │   ├── raylib_render.cpp
    │   └── raylib_render.h
    └── text
        ├── CMakeLists.txt
        ├── main_text.cpp
        ├── text_viewer.cpp
        └── text_viewer.h
```

Le but est de montrer via le `SecondExemple` comment compiler plusieurs exécutables avec certaines parties communes (`main_raylib.cpp` et `main_text.cpp`), tandis que le `QuatriemeExemple` sert à montrer comment ajouter Raygui.

On utilisera les principalement les commandes fonctions suivantes :

```cmake
# Permet la création de macros
set(nom_de_la_macro valeur_de_la_macro)

# Permet de créer un exécutable
add_executable(nom_de_l_executable fichiers_a_compiler)

# Rend accessible les fichiers des dossiers aux autres fichiers du projet
target_include_directories(nom_de_l_executable PRIVATE nom_du_dossier)

# Permet de lier les bibliothèques à l'exécutable
target_link_libraries(nom_de_l_executable nom_de_la_bibliotheque)
```

**TODO : refaire la partie compilation.**

Maintenant que le CMake est configuré, on peut l'utiliser pour compiler le projet. Pour cela, il faut se placer dans le dossier `build` et exécuter les commandes suivantes :

```bash
cmake ..
cmake --build .
```

La commande `cmake ..` va générer les fichiers de construction pour le projet, et est à utiliser après chaque modification du `CMakeLists.txt`. La commande `cmake --build .` va compiler le projet et créer les exécutables. On peut compiler un seul exécutable en ajoutant le nom de celui-ci à la fin de la commande, par exemple `cmake --build . --target nom_de_l_executable`. L'intérêt d'être dans un dossier `build` est que cela garde le projet propre, en mettant tous les fichiers de construction dans le dossier `build`.

> Parfois, le compilateur peut réutiliser un fichier d'une compilation précédente s'il ne détecte pas de changement dans le code. Cela peut parfois laisser une erreur pourtant réglée. Dans ce cas, supprimer les fichiers du dossier `build` et relancer la commande `cmake ..`, puis `cmake --build .` peut aider à résoudre le problème.

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

Pour pouvoir afficher quelque chose, nous commençons par initialiser la fenêtre. On peut le faire en utilisant la fonction `InitWindow`, qui prend en argument la largeur et la hauteur de la fenêtre, ainsi qu'un titre. Il faut ensuite faire une boucle d'affichage, qui se termine lorsque l'utilisateur ferme la fenêtre. Finalement, il ne faut pas oublier de libérer les ressources utilisées par Raylib via la fonction `CloseWindow`.

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

Il y a également la possibilité d'afficher des formes géométriques. Par exemple, on peut afficher un cercle via la fonction `DrawCircle`, qui prend en argument le centre du cercle, son rayon, sa couleur et sa bordure ([on trouvera ici d'autres exemples de formes 2D](https://www.raylib.com/examples/shapes/loader.html?name=shapes_basic_shapes)).

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

Avant de passer à la suite, nous mentionnerons encore plusieurs paramètres pouvant être utiles quant au paramétrage de la fenêtre. Par exemple, il y a un système de `flags` qui permettent de définir le comportement de la fenêtre ([exemple des `flags` possibles](https://www.raylib.com/examples/core/loader.html?name=core_window_flags)). On peut par exemple définir si la fenêtre est redimensionnable, si elle est en plein écran, si elle est visible, etc. On peut également lui fixer une taille minimale afin que nos éléments ne soient pas trop écrasés. Il est aussi commun de fixer un nombre de frames par seconde, pour éviter que le programme ne tourne trop vite.

```c++
// ###########################################################
/*
 * Optionnel, les "flags" permettent de définir le comportement de la fenêtre
 * par exemple le redimensionnement "FLAG_WINDOW_RESIZABLE" ou
 * l'adaptation à la résolution "FLAG_WINDOW_HIGHDPI"
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

> Pour découvrir d'autres exemples et trouver de l'inspiration, on pourra consulter la [galerie d'exemples de Raylib](https://www.raylib.com/examples.html). Il existe également une page regroupant les [différentes fonctions de Raylib](https://www.raylib.com/cheatsheet/cheatsheet.html), mais elle est moins pratique à utiliser.

---

## Deuxième exemple : modularisation et dessin 3D

On va maintenant modulariser notre code. Le but ici est de séparer ce que l'on veut visualiser et le contenu de celui-ci. L'idée est d'organiser le programme selon deux grand principe (dit "[design patterns](https://fr.wikipedia.org/wiki/Patron_de_conception)") :

- Clairement séparer trois choses : la gestion de l'application (le `main` ou le `run`, cf. plus loin), le contenu à afficher et la façon de l'afficher (dans les différentes formes : affichage à l'écran, texte, dans un fichier, ...).
- Et il en suit une claire distinction entre ce qui doit être affiché, et la manière de le faire sur les différents supports, celle-ci ne devant pas intérferer avec le contenu.

> Dans ce qui suit, nous détaillons la démarche, mais il n'est pas nécessaire de tout comprendre dans le détail pour pouvoir bien réutiliser le code fourni. Néanmoins, une fois les connaissances nécessaires à la compréhension de celui-ci acquise, il peut toujours être intéressant de revenir sur les différents choix de conception.

Nous allons séparer le code sur trois grands axes (libre au lecteur d'adapter cela à ses besoins), dans trois répertoires (voir l'arborencense dans ["Installation et compilation"](#installation-et-compilation)) :

### Général

D'un point de vue abstrait, nous différencierons ce qui est dessinable et les supports à dessein, comme dit en préambule. Conceptuellement, le dessinable est le plus simple, il lui suffit d'avoir une méthode permettant de le dessiner sur un support.

```c++
// dessinable.h
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
// support_a_dessin.h
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
// contenu.h
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
// main_text.cpp
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
// text_viewer.h
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
// text_viewer.cpp
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
// main_raylib.cpp
#include "raylib_render.h"

int main()
{
    RaylibRender ecran;
    ecran.run();
}
```

Ici, nous appelons la méthode `dessine_sur` dans la méthode `run`, et nous avons le contenu qui sera un attribut de la classe `RaylibRender`.

```c++
// raylib_render.h
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
// raylib_render.cpp
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

> Il est aussi possible de faire [une caméra dans le cas 2D](https://www.raylib.com/examples/core/loader.html?name=core_2d_camera), mais cela ne sera pas abordé ici.

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

> Les objets peuvent paraitre très plat, car il n'y a pas de système de lumière par défaut, ni de méthode suffisamment simple pour le présenter ici, ce qui fait qu'il n'y a pas d'ombres par exemple (l'[exemple le plus simple](https://www.raylib.com/examples/shaders/loader.html?name=shaders_basic_lighting) gère l'ombre pour chaque objet, et sinon il faudrait faire un système de ["shadow mapping"](https://en.wikipedia.org/wiki/Shadow_mapping)).

![ex2_img2.png](SecondExemple/ex2_img2.png)

---

## Troisième exemple : dessin de plusieurs objets et mouvements de caméra

> Pour les exemples qui suivent, nous nous concentrerons que sur la partie Raylib, et nous ne modifierons pas les fichiers `main_raylib.cpp`, `dessinable.h` et `support_a_dessin.h`.

Afin d'avoir un peu d'intérêt à l'exemple, nous modifions les Contenu comme suit :

```c++
// ...
enum COULEUR {
    NONE,
    ROUGE,
    VERT,
    BLEU,
};

struct Position {
    double x;
    double y;
    double z;
};

class Contenu final : public Dessinable {
public:
    // ...
    Contenu(const Position &p = {0, 0, 0}, const COULEUR c = NONE) : position(p), color(c) {};

    void dessine_sur(SupportADessin &support) override { support.dessine(*this); }

    Position get_position() const { return position; }
    COULEUR get_color() const { return color; }
private:
    Position position;
    COULEUR color;
};
```

Ceci lui ajoute donc une propriété `position` et une couleur, qui sont toutes deux des attributs de la classe, ainsi qu'un getter et un constructeur. Nous pouvons aussi modifier la déclaration de `RaylibRender` afin d'avoir plusieurs contenus à afficher :

```c++
// ...
class RaylibRender final : public SupportADessin {
// ...
private:
    // ...
    std::vector<Contenu> liste_contenus = {
        Contenu(),
        Contenu({-1,1,1}, VERT),
        Contenu({-1,0,1}, ROUGE),
    };
};
```

La méthode `dessine` a été modifiée pour utiliser les propriétés de `Contenu` :

```c++
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
```

La formulation `const auto [x, y, z] = a_dessiner.get_position();` permet de décomposer le `Position` en trois variables `x`, `y` et `z` automatiquement. De plus, pour la position, on doit forcer la conversion en `float` pour éviter des erreurs de compilation, ceci via le `static_cast<float>(...)`.

Finalement, on veut afficher chaque cube dans la méthode `run`, et pour cela, on peut faire une boucle sur la liste des contenus :

```c++
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
```

Si l'on veut permettre le movement de la caméra, il suffit d'ajouter la fonction `UpdateCamera` de Raylib :

```c++
void RaylibRender::run() {
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);
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
```

`UpdateCamera` prend en paramètre la caméra à mettre à jour et le type de mouvement, ici [`CAMERA_FREE`](https://www.raylib.com/examples/core/loader.html?name=core_3d_camera_free), qui gére le mouvement via la souris et les touches `W`, `A`, `S` et `D` (d'autres modes de mouvement sont présentés [ici](https://www.raylib.com/examples/core/loader.html?name=core_3d_camera_first_person)).

L'affichage final ressemble donc à ceci :

![ex3_img.png](TroisiemeExemple/ex3_img.png)

---

## Quatrième exemple : interactivité (souris, clavier, boutons, ...)

Dans ce quatrième exemple, nous allons voir trois interactions possibles :

- Le clavier : utiliser une touche pour activer ou non le déplacement de la caméra.
- La souris : récupérer sa position et l'utiliser pour y dessiner un objet.
- Raygui : utiliser un bouton pour activer une fonctionalité.

Nous allons faire un pointeur rouge qui suit la souris, activable par un bouton. Pour cela, nous devons ajouter deux attributs à la classe `RaylibRender` pour gérer l'état (actif ou non) du mouvement de la caméra et du pointeur :

```c++
// ...
class RaylibRender final : public SupportADessin {
// ...
private:
    // ...
    bool deplacement = false;
    bool pointeur = false;
};
```

On va commencer par activé le déplacement avec la touche `L`. Pour cela, dans notre boucle principale, on va vérifier si la touche `L` est pressée, et si oui, on va changer l'état du déplacement :

```c++
void RaylibRender::run() {
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_L)) {
            deplacement = !deplacement;
        }
        // ...
    }
}
```

Ensuite, on va mettre à jour la caméra seulement si le déplacement est activé :

```c++
void RaylibRender::run() {
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_L)) {
            deplacement = !deplacement;
        }
        if (deplacement) {
            UpdateCamera(&camera, CAMERA_FREE);
        }
        // ...
    }
}
```

Et on peut ajouter un message à l'écran pour indiquer si le déplacement est activé ou non :

```c++
void RaylibRender::run() {
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_L))
            deplacement = !deplacement;

        if (deplacement)
            UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                for (auto& contenu : liste_contenus) {
                    contenu.dessine_sur(*this);
                }
            EndMode3D();

            DrawText("Appuyez sur 'L' pour activer/désactiver le mouvement de la caméra", 10, 10, 20, DARKGRAY);
            DrawText((std::string("Caméra ") + (deplacement ? "libre" : "fixe")).c_str(), 10, 40, 20, DARKGRAY);
        EndDrawing();
    }
}
```

Pour que le texte soit correctement visible, on ne le dessine pas dans le mode 3D, mais après l'avoir quitté. Pour le [paramétrage du texte](https://www.raylib.com/examples/text/loader.html?name=text_format_text), on donne la chaîne de caractères à afficher, la position du texte (les deux premiers arguments numériques), la taille de la police et la couleur du texte. En cas d'utilisation d'une `string` C++, il faut la convertir en chaîne à la C via la méthode `c_str()`.

| Mouvement OFF                                      | Mouvement ON                                           |
|----------------------------------------------------|--------------------------------------------------------|
| ![ex4_camfix.png](QuatriemeExemple/ex4_camfix.png) | ![ex4_camlibre.png](QuatriemeExemple/ex4_camlibre.png) |

Nous allons maintenant voir comment ajouter un bouton. Pour cela, nous allons utiliser la bibliothèque Raygui, que l'on importe comme suit :

```c++
// raylib_render.cpp
// ...
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#undef RAYGUI_IMPLEMENTATION
// ...
```

> Dû à sa conception, mettre `#define RAYGUI_IMPLEMENTATION` avant d'inclure le fichier d'en-tête est nécessaire pour que Raygui fonctionne.

Sur le GitHub de [Raygui](https://github.com/raysan5/raygui), nous pouvons trouver [les différents composants disponibles](https://github.com/raysan5/raygui?tab=readme-ov-file#basic-controls), ainsi que divers programmes pouvant être utile pour réfléchir à l'interface graphique, comme un [éditeur de layout](https://raylibtech.itch.io/rguilayout) ou [d'icones](https://raylibtech.itch.io/rguiicons), et des exemples d'utilisation.

Pour ce que nous allons faire, le plus adapté est un bouton ON/OFF ("toggle"), que l'on peut créer comme suit :

```c++
void RaylibRender::run() {
    while (!WindowShouldClose()) {
        // ...
        BeginDrawing();
            // ...
            GuiToggle(Rectangle(10, 560, 60, 30), "Pointeur", &pointeur);
        EndDrawing();
    }
}
```

Le toggle prend en argument un rectangle (la position et la taille du bouton), le texte à afficher et un pointeur vers une variable booléenne qui va changer d'état lorsque l'on clique sur le bouton.

> Pour un bouton classique, l'utilisation est un peu différente :
> ```c++
> while (!WindowShouldClose()) {
>       // ...
>       BeginDrawing();
>           // ...
>           if (GuiButton((Rectangle){ X, Y, Longueur, Largeur }, "Texte")) {
>               // Action à réaliser
>           }
>       EndDrawing();
>   }
> ```
> Donc il ne faut pas hésiter à chercher comment s'utilise un composant avant de l'utiliser.

Pour récupérer la position de la souris, on peut utiliser la fonction `GetMousePosition`, qui renvoie un `Vector2` avec les coordonnées de la souris. On peut alors dessiner un cercle à cette position :

```c++
void RaylibRender::run() {
    while (!WindowShouldClose()) {
        // ...
        BeginDrawing();
            // ...
            GuiToggle(Rectangle(10, 560, 60, 30), "Pointeur", &pointeur);
            if (pointeur) {
                auto [x, y] = GetMousePosition();
                DrawCircle(static_cast<int>(x), static_cast<int>(y), 10.0f, RED);
            }
        EndDrawing();
    }
}
```

Ce qui nous donne un affichage comme suit :

| Pointeur OFF                                     | Pointeur ON                                       |
|--------------------------------------------------|---------------------------------------------------|
| ![ex4_camfix.png](QuatriemeExemple/ex4_poff.png) | ![ex4_camlibre.png](QuatriemeExemple/ex4_pon.png) |

> Il est aussi possible de faire [un bouton sans utiliser Raygui](https://www.raylib.com/examples/textures/loader.html?name=textures_sprite_button), mais cela est sensiblement plus complexe.

---

## Cinquième exemple : évolution en temps réel

### Un peu de théorie

### L'exemple

Pour cet exemple, nous repartons des fichiers de [l'exemple 2](#deuxième-exemple--modularisation-et-dessin-3d), et nous modifions le Contenu afin qu'il ait un angle de rotation, un getter, ainsi qu'une méthode faisant évoluer cet angle pendant `dt` :

```c++
class Contenu final : public Dessinable {
public:
    // ...
    double get_angle() const { return angle; }

    void evolue(const double dt) {
        angle += 10*dt;
    }
private:
    double angle = 0;
};
```

---

## Sixième exemple : ajout d'objets plus complexes

---

## Conclusion
