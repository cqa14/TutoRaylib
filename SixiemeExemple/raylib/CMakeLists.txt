add_library(Ex6RayRender raylib_render.h raylib_render.cpp)
target_link_libraries(Ex6RayRender raylib Ex6Dessin)
file(COPY ${PROJECT_SOURCE_DIR}/SixiemeExemple/monkey.glb DESTINATION ${CMAKE_BINARY_DIR}/bin/ressources)

add_executable(Exemple6 main_raylib.cpp)
target_link_libraries(Exemple6 Ex6RayRender)