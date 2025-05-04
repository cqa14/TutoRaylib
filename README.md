# Tuto Raylib

> Il existe de nombreuses autres bibliothèques permettant de créer des interfaces graphiques, comme [Qt](https://qt.io/), [GLFW](https://www.glfw.org/), [OGRE](https://www.ogre3d.org/), [wxWidgets](https://www.wxwidgets.org/), ou encore [SDL](https://www.libsdl.org/), qui ont chacunes leurs avantages et inconvénients, donc il ne faut surtout pas hésiter à regarder s'il y en a une semblant plus adaptée à un projet particulier.

## Introduction

Dans la vie courante, il est rare d'intéragir avec un programme directement par le terminal. Les interfaces graphiques offrent de nouvelles possibilités d'affichage ainsi qu'une expérience utilisateur plus agréable. Ce document vise à donner un aperçu de Raylib, une bibliothèque permettant de créer des interfaces graphiques en C++.

> [Raylib](https://www.raylib.com) est à l'origine une bibliothèque C, pensée pour programmer des jeux vidéo à l'origine. Elle a l'avantage d'être relativement simple à utiliser, et d'avoir été portée dans de nombreux langages et sur toutes les plateformes. Son origine du C fait que certains exemples de la documentation doivent être quelque peu adaptés pour être dans un style plus proche du C++.

---

## Installation et compilation

Afin de faciliter l'usage de Raylib, nous allons utiliser [CMake](https://cmake.org/), mais l'usage d'un MAKEFILE est également possible si Raylib est disponible sur le système, en ajoutant le flag `-lraylib`. Nous laisserons le soin au lecteur de regarder comment faire l'installation si cela l'intéresse ([référence d'installation sur le GitHub de Raylib](https://github.com/raysan5/raylib?tab=readme-ov-file#build-and-installation)).

Avec CMake, on pourra directement installer Raylib pour le projet, ce qui permet de ne pas avoir à s'en soucier sur chaque appareil sur lequel on sera amené à travailler. Pour commencer, il faut créer un fichier `CMakeLists.txt` à la racine du projet, qui contiendra les instructions de construction pour les différents exécutables. On commence par indiquer la version minimale de CMake requise, ainsi que la version de C++ à utiliser. On peut également indiquer le nom du projet et sa version.

```cmake title="CMakeLists.txt"
cmake_minimum_required(VERSION 3.21)
project(NOM_DU_PROJET)
set(CMAKE_CXX_STANDARD 20)
```

Ensuite, on peut ajouter les instructions pour vérifier si Raylib est installé sur le système, et s'il ne l'est pas, de l'installer. Si l'on désire avoir accès à des boutons, on peut également ajouter l'installation de [Raygui](https://github.com/raysan5/raygui) (une autre option pour Raygui est de copier le [header](https://github.com/raysan5/raygui/blob/master/src/raygui.h) dans le projet et de le traiter comme un header classique).

```cmake
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
│   │   ├── contenu.h
│   │   ├── dessinable.h
│   │   └── support_a_dessin.h
│   └── raylib
│       ├── main_raylib.cpp
│       ├── raylib_render.cpp
│       └── raylib_render.h
└── SecondExemple
    ├── CMakeLists.txt
    ├── general
    │   ├── contenu.h
    │   ├── dessinable.h
    │   └── support_a_dessin.h
    ├── raylib
    │   ├── main_raylib.cpp
    │   ├── raylib_render.cpp
    │   └── raylib_render.h
    └── text
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

Par exemple, pour `main_text.cpp` qui ne nécessite pas Raylib, on peut écrire dans `CMakeLists.txt` dans le dossier `SecondExemple` :

```cmake
# Configuration de l'exécutable pour l'exemple 2
set(HeaderExemple2 general/contenu.h
        general/dessinable.h
        general/support_a_dessin.h)

# Texte
set(Exemple2Text ${PROJECT_NAME}_Exemple2Text)
add_executable(${Exemple2Text} text/main_text.cpp
        text/text_viewer.h
        text/text_viewer.cpp
        ${HeaderExemple2})
target_include_directories(${Exemple2Text} PRIVATE general text)
```

Comme on aura besoin des headers aussi pour le `main_raylib.cpp`, ils ont été mis dans une variable `HeaderExemple2`, que l'on peut appeler dès que l'on en a besoin via `${HeaderExemple2}`. On a également fait une macro pour le nom de l'exécutable, qui est `Exemple2Text`, permettant que le nom de l'exécutable prenne celui du projet (via `${PROJECT_NAME}`) puis le nom de l'exemple `NOM_DU_PROJET_Exemple2Text`, mais cela peut être simplifié à volonté :

```cmake
add_executable(Exemple2Text text/main_text.cpp
        text/text_viewer.h
        text/text_viewer.cpp
        ${HeaderExemple2})
target_include_directories(Exemple2Text PRIVATE general text)
```

Dans cette version, le nom est tout simplement `Exemple2Text`. Le seul point important est que ce soit le même entre la fonction `add_executable` et `target_include_directories`.

Si l'on veut maintenant un autre exécutable, par exemple `main_raylib.cpp` de `SecondExemple`, on peut faire de même :

```cmake
# Raylib
set(Exemple2Raylib ${PROJECT_NAME}_Exemple2Raylib)
add_executable(${Exemple2Raylib} raylib/main_raylib.cpp
        raylib/raylib_render.cpp
        raylib/raylib_render.h
        ${HeaderExemple2})
target_include_directories(${Exemple2Raylib} PRIVATE general raylib)
target_link_libraries(${Exemple2Raylib} raylib)
```

Pour celui-ci, nous ajoutons également la bibliothèque Raylib, ce qui fait que l'on doit ajouter `target_link_libraries(${Exemple2Raylib} raylib)`.

Pour ajouter Raygui à un exécutable, il suffit d'ajouter le dossier où se trouve le header à l'exécutable (`${raygui_SOURCE_DIR}/src` si installé comme suggéré) :

```cmake
# Configuration de l'exécutable pour l'exemple 4
set(HeaderExemple4 general/contenu.h
        general/dessinable.h
        general/support_a_dessin.h)

# Raylib
set(Exemple4 ${PROJECT_NAME}_Exemple4)
add_executable(${Exemple4} raylib/main_raylib.cpp
        raylib/raylib_render.cpp
        raylib/raylib_render.h
        ${HeaderExemple4})
target_include_directories(${Exemple4} PRIVATE general raylib)
target_link_libraries(${Exemple4} raylib)
target_include_directories(${Exemple4} PRIVATE ${raygui_SOURCE_DIR}/src)
```

> On note qu'on n'a jamais explicitement lié Raygui, mais seulement indiqué le dossier où se trouve le header. Ceci est dû à deux choses :
> 
> - Raygui est un header unique, et il n'y a pas de bibliothèque à lier.
> - Il n'est pas strictemment nécessaire de mettre les `.h` dans le `add_executable` tant que les dossiers de ceux-ci sont mis dans `target_include_directories`, mais cela permet de garder une certaine clarté dans le code et est utile à certains IDE pour savoir quels fichiers sont utilisés, et à CMake pour contrôler les différences suites à des modifications.

Il faut finalement indiquer au CMake principale de chercher dans les sous-dossiers pour trouver les `CMakeLists.txt` des exemples. Pour cela, il suffit d'ajouter les lignes suivantes :

```cmake
add_subdirectory(SecondExemple)
add_subdirectory(QuatriemeExemple)
```

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

> Les objets peuvent paraitre très plat, car il n'y a pas de système de lumière par défaut, ni de méthode suffisamment simple pour le présenter ici, ce qui fait qu'il n'y a pas d'ombres par exemple.

![ex2_img2.png](SecondExemple/ex2_img2.png)

---

## Troisième exemple : dessin de plusieurs objets et mouvements de caméra

---

## Quatrième exemple : interactivité (souris, clavier, boutons, ...)

---

## Cinquième exemple : évolution en temps réel

---

## Sixième exemple : ajout d'objets plus complexes

---

## Conclusion
