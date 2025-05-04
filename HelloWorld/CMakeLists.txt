####################################################################
# Configuration de l'exécutable pour le Hello World

set(HELLO ${PROJECT_NAME}_Hello)
add_executable(${HELLO} hello.cpp)
target_link_libraries(${HELLO} raylib)
target_include_directories(${HELLO} PRIVATE ${raygui_SOURCE_DIR}/src)