####################################################################
# Configuration de l'exécutable pour l'exemple 6
set(HeaderExemple6 general/contenu.h
        general/dessinable.h
        general/support_a_dessin.h)

# Raylib
set(Exemple6 ${PROJECT_NAME}_Exemple6)
add_executable(${Exemple6} raylib/main_raylib.cpp
        raylib/raylib_render.cpp
        raylib/raylib_render.h
        ${HeaderExemple5})
target_include_directories(${Exemple6} PRIVATE general
        raylib)
target_link_libraries(${Exemple6} raylib)