add_library(Ex4RayRender raylib_render.h raylib_render.cpp)
target_link_libraries(Ex4RayRender raylib Ex4Dessin)
target_include_directories(Ex4RayRender PRIVATE ${raygui_SOURCE_DIR}/src)

add_executable(Exemple4 main_raylib.cpp)
target_link_libraries(Exemple4 Ex4RayRender)