####################################################################
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
target_include_directories(${Exemple2Text} PRIVATE general
        text)

# Raylib
set(Exemple2Raylib ${PROJECT_NAME}_Exemple2Raylib)
add_executable(${Exemple2Raylib} raylib/main_raylib.cpp
        raylib/raylib_render.cpp
        raylib/raylib_render.h
        ${HeaderExemple2})
target_include_directories(${Exemple2Raylib} PRIVATE general
        raylib)
target_link_libraries(${Exemple2Raylib} raylib)