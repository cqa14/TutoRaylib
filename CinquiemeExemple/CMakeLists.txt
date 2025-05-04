####################################################################
# Configuration de l'exécutable pour l'exemple 5
set(HeaderExemple5 general/contenu.h
        general/dessinable.h
        general/support_a_dessin.h)

# Raylib
set(Exemple5 ${PROJECT_NAME}_Exemple5)
add_executable(${Exemple5} raylib/main_raylib.cpp
        raylib/raylib_render.cpp
        raylib/raylib_render.h
        ${HeaderExemple5})
target_include_directories(${Exemple5} PRIVATE general
        raylib)
target_link_libraries(${Exemple5} raylib)