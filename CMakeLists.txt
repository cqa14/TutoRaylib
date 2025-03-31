cmake_minimum_required(VERSION 3.30)
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
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_Declare(
    raygui
    GIT_REPOSITORY "https://github.com/raysan5/raygui.git"
    GIT_TAG "master"
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

####################################################################
