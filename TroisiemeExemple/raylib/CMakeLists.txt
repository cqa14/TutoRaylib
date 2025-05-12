add_library(Ex3RayRender raylib_render.h raylib_render.cpp)
target_link_libraries(Ex3RayRender raylib Ex3Dessin)

add_executable(Exemple3 main_raylib.cpp)
target_link_libraries(Exemple3 Ex3RayRender)