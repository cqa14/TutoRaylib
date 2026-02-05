add_library(Ex5RayRender raylib_render.h raylib_render.cpp)
target_compile_options(Ex5RayRender PRIVATE ${PROJECT_WARNING_FLAGS})
target_link_libraries(Ex5RayRender raylib Ex5Dessin)

add_executable(Exemple5 main_raylib.cpp)
target_compile_options(Exemple5 PRIVATE ${PROJECT_WARNING_FLAGS})
target_link_libraries(Exemple5 Ex5RayRender)
