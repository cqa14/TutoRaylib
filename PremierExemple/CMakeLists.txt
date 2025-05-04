####################################################################
# Configuration de l'exécutable pour l'exemple 1

set(Exemple1 ${PROJECT_NAME}_Exemple1)
add_executable(${Exemple1} main_exemple1.cpp)
target_link_libraries(${Exemple1} raylib)