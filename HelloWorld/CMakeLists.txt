####################################################################
# Configuration de l'exécutable pour le Hello World

add_executable(HELLO hello.cpp)
target_link_libraries(HELLO raylib)
target_include_directories(HELLO PRIVATE ${raygui_SOURCE_DIR}/src)