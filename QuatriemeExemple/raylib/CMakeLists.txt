add_library(Ex4RayRender raylib_render.h raylib_render.cpp)
target_include_directories(Ex4RayRender PRIVATE ${raygui_SOURCE_DIR}/src)
target_compile_options(Ex4RayRender PRIVATE -Wno-enum-compare)
target_link_libraries(Ex4RayRender raylib Ex4Dessin)

add_executable(Exemple4 main_raylib.cpp)
target_compile_options(Exemple4 PRIVATE ${PROJECT_WARNING_FLAGS})
target_link_libraries(Exemple4 Ex4RayRender)
