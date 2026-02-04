add_library(Ex2RayRender raylib_render.h raylib_render.cpp)
target_include_directories(Ex2RayRender PUBLIC ${PROJECT_SOURCE_DIR}/DeuxiemeExemple/general)
target_compile_options(Ex2RayRender PRIVATE ${PROJECT_WARNING_FLAGS} -Wno-unused-parameter)
target_link_libraries(Ex2RayRender raylib Ex2Dessin)

add_executable(Exemple2Raylib main_raylib.cpp)
target_include_directories(Exemple2Raylib PUBLIC ${PROJECT_SOURCE_DIR}/DeuxiemeExemple/general)
target_compile_options(Exemple2Raylib PRIVATE ${PROJECT_WARNING_FLAGS})
target_link_libraries(Exemple2Raylib Ex2RayRender)
