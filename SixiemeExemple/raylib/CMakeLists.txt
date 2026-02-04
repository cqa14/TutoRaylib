add_library(Ex6RayRender raylib_render.h raylib_render.cpp)
target_compile_options(Ex6RayRender PRIVATE ${PROJECT_WARNING_FLAGS} -Wno-unused-parameter)
target_link_libraries(Ex6RayRender raylib Ex6Dessin)
file(COPY ${PROJECT_SOURCE_DIR}/SixiemeExemple/monkey.glb DESTINATION ${CMAKE_BINARY_DIR}/bin/ressources)

add_executable(Exemple6 main_raylib.cpp)
target_compile_options(Exemple6 PRIVATE ${PROJECT_WARNING_FLAGS})
target_link_libraries(Exemple6 Ex6RayRender)
