####################################################################
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
target_include_directories(${Exemple4} PRIVATE general
        raylib)
target_link_libraries(${Exemple4} raylib)
target_include_directories(${Exemple4} PRIVATE ${raygui_SOURCE_DIR}/src)