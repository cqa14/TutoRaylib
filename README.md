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

Avec CMake, on pourra directement installer Raylib pour le projet, ce qui permet de ne pas avoir à s'en soucier sur chaque appareil sur lequel on sera amené à travailler. Pour commencer, il faut créer un fichier `CMakeLists.txt` à la racine du projet, qui contiendra les instructions de construction pour les différents exécutables. On commence par indiquer la version minimale de CMake requise, ainsi que la version de C++ à utiliser. On peut également indiquer le nom du projet et sa version. Finalement, on ajoute les instructions pour définir les répertoires de sortie des exécutables et des bibliothèques afin de les retrouver facilement.

```cmake 
# CMakeLists.txt
cmake_minimum_required(VERSION 3.21)
project(NOM_DU_PROJET)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
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
└── SixiemeExemple
    ├── CMakeLists.txt
    ├── general
    │   ├── CMakeLists.txt
    │   ├── contenu.h
    │   ├── dessinable.h
    │   └── support_a_dessin.h
    ├── monkey.glb
    └── raylib
        ├── CMakeLists.txt
        ├── main_raylib.cpp
        ├── raylib_render.cpp
        └── raylib_render.h
```

Le fichier `CMakeLists.txt` traiter jusqu'à présent est celui de la racine du projet, et il faut encore lui ajouter les sous-répertoires où chercher les fichiers sources et les headers.

```cmake
# CMakeLists.txt
# ...
add_subdirectory(QuatriemeExemple)
add_subdirectory(SixiemeExemple)
```

On présente maintenant la configuration pour le quatrième et le sixième exemple, car ils présentent chacun des particularités utiles à savoir. Le quatrième, outre Raylib, il utilise aussi Raygui, et le sixième exemple utilise un modèle 3D, ce qui nécessite de le copier pour le rendre accessible au programme.

Dans tous les cas, on ajoute dans chaque sous-dossier un fichier `CMakeLists.txt` qui va gérer tout ce qu'il y a dans celui-ci. Dans ceux où il n'y a pas de fichiers particuliers, par exemple dans `QuatriemeExemple`, on inclut simplement les sous-dossiers `general` et `raylib`, qui contiennent notre programme.

```cmake
# QuatriemeExemple/CMakeLists.txt
add_subdirectory(general)
add_subdirectory(raylib)
```

Pour le dossier `general`, on va créer une librairie avec les fichiers `contenu.h`, `dessinable.h` et `support_a_dessin.h`, qui pourra être utilisée dans le reste du projet.

```cmake
# QuatriemeExemple/general/CMakeLists.txt
add_library(Ex4Dessin contenu.h dessinable.h support_a_dessin.h)
set_target_properties(Ex4Dessin PROPERTIES LINKER_LANGUAGE CXX) # Car CMake ne peut pas le deviner (.h est commun à C et C++)
target_include_directories(Ex4Dessin PUBLIC ${PROJECT_SOURCE_DIR}/QuatriemeExemple/general)
```

> Quand il n'y a que des fichiers `.h`, il faut spécifier que ce sont des fichiers C++ avec `LINKER_LANGUAGE CXX`, sinon cela fait une erreur. De plus, pour que d'autres fichiers puissent utiliser cette librairie, il faut ajouter le dossier contenant les headers avec `target_include_directories`.

Dans le dossier `raylib`, on va créer une librairie qui va contenir le fichier `raylib_render.cpp` et son header, et un exécutable à partir du fichier `main_raylib.cpp`. À noter que pour la librairie, on va lier toutes les librairies que l'on utilise dans celle-ci, donc Raylib et la librairie `Ex4Dessin` que l'on vient de créer, mais on a ensuite plus besoin de s'en soucier au moment d'utiliser cette nouvelle librairie.

```cmake
# QuatriemeExemple/raylib/CMakeLists.txt
add_library(Ex4RayRender raylib_render.h raylib_render.cpp)
target_link_libraries(Ex4RayRender raylib Ex4Dessin)
target_include_directories(Ex4RayRender PRIVATE ${raygui_SOURCE_DIR}/src)

add_executable(Exemple4 main_raylib.cpp)
target_link_libraries(Exemple4 Ex4RayRender)
```

> Comme Raygui est un header, il faut inclure son dossier dans la cible l'utilisant, dans ce cas `Ex4RayRender`, avec `target_include_directories`.

Pour le sixième exemple, c'est identique. On ajoute juste une ligne pour copier le modèle 3D dans le dossier de sortie (`${CMAKE_BINARY_DIR}/bin` configuré au tout début de cette section), afin qu'il soit accessible au programme. 

```cmake
# SixiemeExemple/raylib/CMakeLists.txt
add_library(Ex6RayRender raylib_render.h raylib_render.cpp)
target_link_libraries(Ex6RayRender raylib Ex6Dessin)
file(COPY ${PROJECT_SOURCE_DIR}/SixiemeExemple/monkey.glb DESTINATION ${CMAKE_BINARY_DIR}/bin/ressources)

add_executable(Exemple6 main_raylib.cpp)
target_link_libraries(Exemple6 Ex6RayRender)
```

Maintenant que le CMake est configuré, on peut l'utiliser pour compiler le projet. Pour cela, il faut se placer dans le dossier `build` et exécuter les commandes suivantes :

```bash
cmake ..
cmake --build .
```

La commande `cmake ..` va générer les fichiers de construction pour le projet, et est à utiliser après chaque modification du `CMakeLists.txt`. La commande `cmake --build .` va compiler le projet et créer les exécutables. On peut compiler un seul exécutable en ajoutant le nom de celui-ci à la fin de la commande, par exemple `cmake --build . --target nom_de_l_executable`. L'intérêt d'être dans un dossier `build` est que cela garde le projet propre, en mettant tous les fichiers de construction dans le dossier `build`.

> Parfois, le compilateur peut réutiliser un fichier d'une compilation précédente s'il ne détecte pas de changement dans le code. Cela peut parfois laisser une erreur pourtant réglée. Dans ce cas, supprimer les fichiers du dossier `build` et relancer la commande `cmake ..`, puis `cmake --build .` peut aider à résoudre le problème.

Pour exécuter un des exécutables, il suffit de se placer dans le dossier `bin` générer dans celui `build` et d'exécuter la commande `./nom_de_l_executable`.

> Note : la plupart des éditeurs de code permettent de définir des configurations permettant de faire ces builds et exécutions dans un dossier autre, sans devoir passer par le terminal.

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

Le dessin d'un cube se fait alors en appelant la fonction `DrawCube` avec en argument la position de celui-ci, sa largeur, sa hauteur, sa profondeur et sa couleur ([on trouvera ici d'autres exemples de figures 3D](https://www.raylib.com/examples/models/loader.html?name=models_geometric_shapes)).

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

Le terme "temps réel" représente le fait que le temps (physique) qui s'écoule a une signification dans le programme. Jusqu'ici dans vos programmes, l'utilisateur pouvait attendre 1 ou 10 minutes à l'invite d'un `cin` sans que cela ne change en rien le comportement du programme. Dans un processus "temps réel", le programme continue par contre de s'exécuter, que l'utilisateur agisse ou non. Ceci permet par exemple d'animer de façon réaliste les éléments du monde que l'on représente.

Considérons le cas d'une balle qu'on lâche depuis une certaine hauteur. On pourrait, comme dans l'exercice que vous avez fait au premier semestre, calculer à l'avance le temps au bout duquel la balle touchera le sol. Mais dans une simulation physique en temps réel, on voudrait avoir la position de la balle à chaque instant, par exemple pour pouvoir l'afficher.

On doit donc pouvoir être capable de décrire à chaque instant la nouvelle position de la balle en fonction de la position précédente et du temps dt écoulé entre deux calculs. Ce temps est simplement le temps que l'ordinateur a mis pour calculer et afficher la dernière position.

Dans une simulation numérique non temps réel, cet intervalle $dt$ est fixé à une valeur arbitraire, aussi petite que la précision de calcul voulue le nécessite (voir cours d'analyse numérique).

Dans un programme "temps réel", c'est par contre la puissance de la machine qui détermine la valeur de $dt$ : plus la scène est complexe à animer et afficher, plus $dt$ sera grand, et plus la simulation sera approximative et l'animation saccadée.

> NOTE : La raison pour laquelle on ne fixe pas à l'avance l'intervalle dt est qu'on a a priori aucune idée du temps que prendra le calcul (et l'affichage !) d'une image et, surtout, qu'on n'a aucune garantie que ce temps restera constant : plus il y a d'éléments à prendre en compte, plus ce temps augmentera. On s'en rend bien compte dans certains jeux vidéos : lorsqu'il y a un phénomène complexe (p.ex. une explosion) ou trop d'unités à gérer, c'est le nombre d'images par seconde qui diminue et non le temps qui se dilate.

Concrètement, $dt$ est donné par l'écart entre l'image précédente et l'image actuelle, et il est calculé à chaque itération de la boucle principale du programme.

La simulation est donc une boucle qui répète en permanence plusieurs étapes, parmi lesquelles :

1. Calcul (ou mise à jour) : on détermine l'état suivant du système, à partir de l'état courant et du pas de temps $dt$ ; c'est dans cette phase que dans votre projet interviendront les équations de la simulation ;
2. Affichage à l'écran (ou sur tout autre support à dessin) : on envoie les données vers la carte vidéo (ou sur cin ou dans un fichier, etc.) ;
3. Gestion des interactions (clavier, souris).

En théorie, aucun calcul concernant la simulation n'est à effectuer dans ces deux dernières phases.

Enfin, lorsqu'une certaine condition d'arrêt est atteinte (p.ex. un certain délai dépassé, une précision suffisante ou un évènement particulier [p.ex. clavier]), on arrête simplement le programme.

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

On modifie alors la méthode `run` de `RaylibRender` pour faire évoluer le contenu à chaque itération de la boucle principale :

```c++
void RaylibRender::run() {
    while (!WindowShouldClose()) {
        const auto dt = GetFrameTime();
        c.evolue(dt);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                DrawGrid(200, 0.5f);

                c.dessine_sur(*this);
            EndMode3D();
        EndDrawing();
    }
}
```

On remarque que le dessin est identique au second exemple, le seul changement est que l'on récupère le temps écoulé depuis la dernière image avec `GetFrameTime`, et que l'on fait évoluer le contenu en appelant la méthode `evolue` avec ce temps.

Maintenant, il faut modifier la méthode `dessine` pour prendre en compte l'angle de rotation. On va pour cela utiliser la librairie `rlgl` de Raylib, qui permet de faire des transformations sur les objets 3D par des matrices ([ci-joint](https://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/) un document lié à OpenGl sur le sujet, qui est la librairie sur laquelle est construite Raylib).

```c++
// ...
#include <rlgl.h>
// ...
void RaylibRender::dessine(Contenu const& a_dessiner) {
    Vector3 cubePosition = { 0.0f, 1.0f, 0.0f };
    
    rlPushMatrix();
    rlRotatef(static_cast<float>(a_dessiner.get_angle()), 0.0f, 1.0f, 0.0f);
    DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, LIME);
    DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, DARKGREEN);
    rlPopMatrix();
}
```

> Si l'on désirait seulement mettre à jour la position du cube, il suffirait de changer son vecteur de position sans se soucier de ces transformations.

Décortiquons ce qui se passe. La fonction `rlPushMatrix` commence les transformations qui seront appliquées jusqu'à l'appel de `rlPopMatrix`. On applique ensuite celles que l'on veut effectuer, ici une rotation autour de l'axe Y, avec `rlRotatef`, qui prend en paramètre l'angle de rotation (en degrés) et les coordonnées de l'axe de rotation (on trouvera [ici](https://www.raylib.com/examples/models/loader.html?name=models_rlgl_solar_system) un exemple plus complexe ainsi que d'autres possibilités offertes par `rlgl`).

On devrait alors avoir :
![ex5_img.png](CinquiemeExemple/ex5_img.png)

---

## Sixième exemple : ajout d'objets plus complexes

Comme pour l'exemple précédent, nous allons repartir de l'exemple 2. Le but de cet exemple est de montrer comment ajouter un modèle 3D plus complexe, que ce soit fait via un logiciel de modélisation 3D ou en utilisant un modèle déjà existant. 

> Dans notre cas, nous avons juste utilisé un modèle par défaut de [Blender](https://www.blender.org/) que l'on a texturé (il existe de nombreuses ressources en ligne pour apprendre ce logiciel si la curiosité vous y pousse, tel que ce [tutoriel](https://www.youtube.com/watch?v=B0J27sf9N1Y&list=PLjEaoINr3zgEPv5y--4MKpciLaoQYZB1Z)).
> ![ex6_blender.png](SixiemeExemple/ex6_blender.png)

Pour commencer, nous allons ajouter à notre classe `RaylibRender` un attribut pour le modèle 3D que nous allons charger :

```c++
// ...
class RaylibRender final : public SupportADessin {
    // ...
private:
    // ...
    Model myModel{};
};
```

Puis pour pouvoir utiliser ce modèle, nous devons le charger dans le constructeur de `RaylibRender` (et l'enlever dans le destructeur) :

```c++
RaylibRender::RaylibRender() {
    // ...
    myModel = LoadModel("ressources/monkey.glb");
}

RaylibRender::~RaylibRender() {
    UnloadModel(myModel);
    CloseWindow();
}
```

> Si le modèle n'est pas à l'endroit, on peut utiliser  :
> ```
>  myModel.transform = MatrixRotateXYZ((Vector3){DEG2RAD * AngleX, DEG2RAD * AngleY, DEG2RAD * AngleZ});
> ```

Le chemin `ressources/monkey.glb` est celui que l'on a paramétré dans le CMake (voir [Installation et compilation](#installation-et-compilation)).

Pour le dessiner, il suffit d'utiliser la méthode `DrawModel` de Raylib, qui prend en paramètre le modèle à dessiner, sa position, sa taille et sa couleur en cas d'absence de texture :

```c++
void RaylibRender::dessine(Contenu const& a_dessiner) {
    Vector3 modelPosition = { 0.0f, 1.0f, 0.0f };
    DrawModel(myModel, modelPosition, 1.0f, WHITE);
}
```

> On trouvera [ici](https://www.raylib.com/examples/models/loader.html?name=models_loading) les différents types de modèles supportés par Raylib.

Et on obtient directement (notons qu'il y a le même problème d'éclairage qu'avec le cube, ce qui fait paraitre le modèle très plat !) :

![ex6_img.png](SixiemeExemple/ex6_img.png)

---

## Conclusion

Ce tutoriel ne vise qu'à offrir un aperçu de ce que l'on peut faire avec Raylib, et en général avec des bibliothèques graphiques. Néanmoins, il n'est pas exhaustif et quand on ne sait pas comment faire quelque chose, il ne faut pas hésiter à chercher dans la documentation ou alors parmi les exemples. Il ne faut ainsi surtout pas hésiter à regarder les divers liens proposés au fur et à mesure de ce tutoriel, et toute autre ressource à ce sujet paraissant pertinente.

---

## Annexe : Pourquoi apprendre à utiliser une bibliothèque graphique ?

Dans le cadre des études de mathématiques ou de physique, il peut paraitre superflu d'apprendre à utiliser une bibliothèque graphique, car on ne vise pas à développer des applications ou des jeux vidéos. Néanmoins, les compétences acquises dans ce domaine peuvent facilement être transposées pour d'autres cas d'usages. Par exemple, pour visualiser des données, on retrouvera des patterns assez similaires à ceux présentés :

```python
import matplotlib.pyplot as plt
import numpy as np

t = np.linspace(-10, 10, 100)
sig = 1 / (1 + np.exp(-t))

fig, ax = plt.subplots()
ax.axhline(y=0, color="black", linestyle="--")
ax.axhline(y=0.5, color="black", linestyle=":")
ax.axhline(y=1.0, color="black", linestyle="--")
ax.axvline(color="grey")
ax.axline((0, 0.5), slope=0.25, color="black", linestyle=(0, (5, 5)))
ax.plot(t, sig, linewidth=2, label=r"$\sigma(t) = \frac{1}{1 + e^{-t}}$")
ax.set(xlim=(-10, 10), xlabel="t")
ax.legend(fontsize=14)
plt.show()
```

afin de produire un graphique comme suit via le module [`matplotlib`](https://matplotlib.org/) de Python :

![mpl.png](mpl.png)

Il existe aussi des outils d'animation pour de la vulgarisation qui se basent sur de la programmation telle que [manim](https://docs.manim.community/en/stable/), crée par Grant Sanderson, le créateur de la chaîne YouTube [3Blue1Brown](https://www.youtube.com/@3blue1brown).

```python
from manim import *

class FollowingGraphCamera(MovingCameraScene):
    def construct(self):
        self.camera.frame.save_state()

        # create the axes and the curve
        ax = Axes(x_range=[-1, 10], y_range=[-1, 10])
        graph = ax.plot(lambda x: np.sin(x), color=BLUE, x_range=[0, 3 * PI])

        # create dots based on the graph
        moving_dot = Dot(ax.i2gp(graph.t_min, graph), color=ORANGE)
        dot_1 = Dot(ax.i2gp(graph.t_min, graph))
        dot_2 = Dot(ax.i2gp(graph.t_max, graph))

        self.add(ax, graph, dot_1, dot_2, moving_dot)
        self.play(self.camera.frame.animate.scale(0.5).move_to(moving_dot))

        def update_curve(mob):
            mob.move_to(moving_dot.get_center())

        self.camera.frame.add_updater(update_curve)
        self.play(MoveAlongPath(moving_dot, graph, rate_func=linear))
        self.camera.frame.remove_updater(update_curve)

        self.play(Restore(self.camera.frame))
```

produisant une animation comme suit :

![manim.gif](manim.gif)

On trouve des similarités entre chacun de ces outils, avec par exemple quels concepts permettent quelles configurations, comment structurer un code quand on a une idée graphique en tête, etc.

Le choix de Raylib est aussi en quelque sorte dans cette suite d'idée, car elle fournit déjà un bon nombre de fonctionnalités et permet d'arriver assez vite à des résultats satisfaisants. De plus, si dans des cours passés certains ont pu se familiariser avec d'autres bibliothèques graphiques tel que [`pygame`](https://www.pygame.org), des similarités seront évidentes, en comparant ce code issu de la documentation de `pygame` avec ceux que l'on a fait avec Raylib :

```python
# Example file showing a circle moving on screen
import pygame

# pygame setup
pygame.init()
screen = pygame.display.set_mode((1280, 720))
clock = pygame.time.Clock()
running = True
dt = 0

player_pos = pygame.Vector2(screen.get_width() / 2, screen.get_height() / 2)

while running:
    # poll for events
    # pygame.QUIT event means the user clicked X to close your window
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # fill the screen with a color to wipe away anything from last frame
    screen.fill("purple")

    pygame.draw.circle(screen, "red", player_pos, 40)

    keys = pygame.key.get_pressed()
    if keys[pygame.K_w]:
        player_pos.y -= 300 * dt
    if keys[pygame.K_s]:
        player_pos.y += 300 * dt
    if keys[pygame.K_a]:
        player_pos.x -= 300 * dt
    if keys[pygame.K_d]:
        player_pos.x += 300 * dt

    # flip() the display to put your work on screen
    pygame.display.flip()

    # limits FPS to 60
    # dt is delta time in seconds since last frame, used for framerate-
    # independent physics.
    dt = clock.tick(60) / 1000

pygame.quit()
```

On y remarque en effet la préparation de la fenêtre, la boucle principale qui gère les événements, et la fin de la boucle qui ferme la fenêtre, avec des noms de méthodes qui ne sont pas très éloignés.
