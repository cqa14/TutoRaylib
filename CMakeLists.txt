cmake_minimum_required(VERSION 3.21)
project(TutoRaylib)
set(CMAKE_CXX_STANDARD 20)

####################################################################
# Installation de raylib si nécessaire

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

####################################################################
# Configuration de l'exécutable pour le Hello World

set(HELLO ${PROJECT_NAME}_Hello)
add_executable(${HELLO} HelloWorld/hello.cpp)
target_link_libraries(${HELLO} raylib)
target_include_directories(${HELLO} PRIVATE ${raygui_SOURCE_DIR}/src)

####################################################################
# Configuration de l'exécutable pour l'exemple 1

set(Exemple1 ${PROJECT_NAME}_Exemple1)
add_executable(${Exemple1} PremierExemple/main_exemple1.cpp)
target_link_libraries(${Exemple1} raylib)

####################################################################
# Configuration de l'exécutable pour l'exemple 2
set(HeaderExemple2 SecondExemple/general/contenu.h
        SecondExemple/general/dessinable.h
        SecondExemple/general/support_a_dessin.h)

# Texte
set(Exemple2Text ${PROJECT_NAME}_Exemple2Text)
add_executable(${Exemple2Text} SecondExemple/text/main_text.cpp
        SecondExemple/text/text_viewer.h
        SecondExemple/text/text_viewer.cpp
        ${HeaderExemple2})
target_include_directories(${Exemple2Text} PRIVATE SecondExemple/general
        SecondExemple/text)

# Raylib
set(Exemple2Raylib ${PROJECT_NAME}_Exemple2Raylib)
add_executable(${Exemple2Raylib} SecondExemple/raylib/main_raylib.cpp
        SecondExemple/raylib/raylib_render.cpp
        SecondExemple/raylib/raylib_render.h
        ${HeaderExemple2})
target_include_directories(${Exemple2Raylib} PRIVATE SecondExemple/general
        SecondExemple/raylib)
target_link_libraries(${Exemple2Raylib} raylib)

####################################################################
# Configuration de l'exécutable pour l'exemple 3
set(HeaderExemple3 TroisiemeExemple/general/contenu.h
        TroisiemeExemple/general/dessinable.h
        TroisiemeExemple/general/support_a_dessin.h)

# Raylib
set(Exemple3 ${PROJECT_NAME}_Exemple3)
add_executable(${Exemple3} TroisiemeExemple/raylib/main_raylib.cpp
        TroisiemeExemple/raylib/raylib_render.cpp
        TroisiemeExemple/raylib/raylib_render.h
        ${HeaderExemple3})
target_include_directories(${Exemple3} PRIVATE TroisiemeExemple/general
        TroisiemeExemple/raylib)
target_link_libraries(${Exemple3} raylib)

####################################################################
# Configuration de l'exécutable pour l'exemple 4
set(HeaderExemple4 QuatriemeExemple/general/contenu.h
        QuatriemeExemple/general/dessinable.h
        QuatriemeExemple/general/support_a_dessin.h)

# Raylib
set(Exemple4 ${PROJECT_NAME}_Exemple4)
add_executable(${Exemple4} QuatriemeExemple/raylib/main_raylib.cpp
        QuatriemeExemple/raylib/raylib_render.cpp
        QuatriemeExemple/raylib/raylib_render.h
        ${HeaderExemple4})
target_include_directories(${Exemple4} PRIVATE QuatriemeExemple/general
        QuatriemeExemple/raylib)
target_link_libraries(${Exemple4} raylib)
target_include_directories(${Exemple4} PRIVATE ${raygui_SOURCE_DIR}/src)

####################################################################
# Configuration de l'exécutable pour l'exemple 5
set(HeaderExemple5 CinquiemeExemple/general/contenu.h
        CinquiemeExemple/general/dessinable.h
        CinquiemeExemple/general/support_a_dessin.h)

# Raylib
set(Exemple5 ${PROJECT_NAME}_Exemple5)
add_executable(${Exemple5} CinquiemeExemple/raylib/main_raylib.cpp
        CinquiemeExemple/raylib/raylib_render.cpp
        CinquiemeExemple/raylib/raylib_render.h
        ${HeaderExemple5})
target_include_directories(${Exemple5} PRIVATE CinquiemeExemple/general
        CinquiemeExemple/raylib)
target_link_libraries(${Exemple5} raylib)

####################################################################
# Configuration de l'exécutable pour l'exemple 6
set(HeaderExemple6 SixiemeExemple/general/contenu.h
        SixiemeExemple/general/dessinable.h
        SixiemeExemple/general/support_a_dessin.h)

# Raylib
set(Exemple6 ${PROJECT_NAME}_Exemple6)
add_executable(${Exemple6} SixiemeExemple/raylib/main_raylib.cpp
        SixiemeExemple/raylib/raylib_render.cpp
        SixiemeExemple/raylib/raylib_render.h
        ${HeaderExemple5})
target_include_directories(${Exemple6} PRIVATE SixiemeExemple/general
        SixiemeExemple/raylib)
target_link_libraries(${Exemple6} raylib)
