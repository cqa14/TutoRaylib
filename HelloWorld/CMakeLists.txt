####################################################################
# Configuration de l'exécutable pour le Hello World

add_executable(HELLO hello.cpp)
target_include_directories(HELLO PRIVATE ${raygui_SOURCE_DIR}/src)
target_compile_options(HELLO PRIVATE -Wno-enum-compare)
target_link_libraries(HELLO raylib)
