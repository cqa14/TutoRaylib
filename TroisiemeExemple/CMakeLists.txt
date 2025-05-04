####################################################################
# Configuration de l'exécutable pour l'exemple 3
set(HeaderExemple3 general/contenu.h
        general/dessinable.h
        general/support_a_dessin.h)

# Raylib
set(Exemple3 ${PROJECT_NAME}_Exemple3)
add_executable(${Exemple3} raylib/main_raylib.cpp
        raylib/raylib_render.cpp
        raylib/raylib_render.h
        ${HeaderExemple3})
target_include_directories(${Exemple3} PRIVATE general
        raylib)
target_link_libraries(${Exemple3} raylib)