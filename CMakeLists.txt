cmake_minimum_required(VERSION 3.21)
project(TutoRaylib)
set(CMAKE_CXX_STANDARD 20)

####################################################################
# Installation de raylib et raygui

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "5.5"
    GIT_PROGRESS TRUE
)

FetchContent_Declare(
    raygui
    GIT_REPOSITORY "https://github.com/raysan5/raygui.git"
    GIT_TAG "4.0"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib raygui)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/")

####################################################################
# Configuration de l'exécutable pour le Hello World

set(HELLO ${PROJECT_NAME}_Hello)
add_executable(${HELLO} HelloWorld/hello.cpp)
target_sources(${HELLO} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${HELLO} PRIVATE ${PROJECT_INCLUDE} ${raygui_SOURCE_DIR}/src)
target_link_libraries(${HELLO} PRIVATE raylib)

target_compile_definitions(${HELLO} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

####################################################################
# Configuration de l'exécutable pour l'exemple 1

set(Exemple1 ${PROJECT_NAME}_Exemple1)
add_executable(${Exemple1} PremierExemple/main_exemple1.cpp)
target_sources(${Exemple1} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${Exemple1} PRIVATE ${PROJECT_INCLUDE} ${raygui_SOURCE_DIR}/src)
target_link_libraries(${Exemple1} PRIVATE raylib)

target_compile_definitions(${Exemple1} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

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
target_sources(${Exemple2Raylib} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${Exemple2Raylib} PRIVATE ${PROJECT_INCLUDE} ${raygui_SOURCE_DIR}/src)
target_link_libraries(${Exemple2Raylib} PRIVATE raylib)

target_compile_definitions(${Exemple2Raylib} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

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
target_sources(${Exemple3} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${Exemple3} PRIVATE ${PROJECT_INCLUDE} ${raygui_SOURCE_DIR}/src)
target_link_libraries(${Exemple3} PRIVATE raylib)

target_compile_definitions(${Exemple3} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

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
target_sources(${Exemple4} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${Exemple4} PRIVATE ${PROJECT_INCLUDE} ${raygui_SOURCE_DIR}/src)
target_link_libraries(${Exemple4} PRIVATE raylib)

target_compile_definitions(${Exemple4} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

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
target_sources(${Exemple5} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${Exemple5} PRIVATE ${PROJECT_INCLUDE} ${raygui_SOURCE_DIR}/src)
target_link_libraries(${Exemple5} PRIVATE raylib)

target_compile_definitions(${Exemple5} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

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
target_sources(${Exemple6} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${Exemple6} PRIVATE ${PROJECT_INCLUDE} ${raygui_SOURCE_DIR}/src)
target_link_libraries(${Exemple6} PRIVATE raylib)

target_compile_definitions(${Exemple6} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
