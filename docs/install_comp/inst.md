# Installation et compilation

Afin de faciliter l'usage de raylib, nous allons utiliser [CMake](https://cmake.org/) comme outil d'aide à la compilation ; mais l'usage d'un `Makefile` est également possible si raylib est déjà disponible sur le système en ajoutant l'option `-lraylib`. Nous laisserons le soin au lecteur de regarder comment faire l'installation dans ce cas là, si cela l'intéresse ([référence d'installation sur le GitHub de raylib](https://github.com/raysan5/raylib?tab=readme-ov-file#build-and-installation)).

Avec CMake, on pourra directement installer raylib depuis CMake lui-même, ce qui permet de ne pas avoir à s'en soucier sur chaque appareil sur lequel on sera amené à travailler.

Pour commencer, il faut créer un fichier `CMakeLists.txt` à la racine du projet. C'est un simple fichier texte qui contiendra les instructions de construction pour les différents exécutables. On commence par indiquer la version minimale de CMake requise, ainsi que la version de C++ à utiliser. On peut également indiquer le nom du projet et sa version. Finalement, on ajoute les instructions pour définir les dossiers de sortie des exécutables et des bibliothèques afin de les retrouver facilement.

```cmake
# CMakeLists.txt
cmake_minimum_required(VERSION 3.21)
project(NOM_DU_PROJET)
set(CMAKE_CXX_STANDARD 20)
set(PROJECT_WARNING_FLAGS
    -pedantic
    -Wall
    -Wextra
    -Wold-style-cast
    -Woverloaded-virtual
    -Wfloat-equal
    -Wshadow
    -Wwrite-strings
    -Wpointer-arith
    -Wcast-qual
    -Wcast-align
    -Wconversion
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
```

Ensuite, on peut ajouter les instructions pour vérifier si raylib est installé sur le système, et s'il ne l'est pas, de l'installer. Si l'on désire avoir accès à des boutons, on peut également ajouter l'installation de [raygui](https://github.com/raysan5/raygui) (une autre option pour utiliser raygui est de copier le fichier d'en-tête [`raygui.h`](https://github.com/raysan5/raygui/blob/master/src/raygui.h) dans le projet et de le traiter comme un fichier d'en-tête classique).

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