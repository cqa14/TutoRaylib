####################################################################
# Configuration de l'exécutable pour l'exemple 1

add_executable(exemple1 main_exemple1.cpp)
target_compile_options(exemple1 PRIVATE ${PROJECT_WARNING_FLAGS})
target_link_libraries(exemple1 raylib)
