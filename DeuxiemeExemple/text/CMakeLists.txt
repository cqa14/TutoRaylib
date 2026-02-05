add_library(Ex2TextViewer text_viewer.h text_viewer.cpp)
target_compile_options(Ex2TextViewer PRIVATE ${PROJECT_WARNING_FLAGS})
target_link_libraries(Ex2TextViewer Ex2Dessin)

add_executable(Exemple2Text main_text.cpp)
target_compile_options(Exemple2Text PRIVATE ${PROJECT_WARNING_FLAGS})
target_link_libraries(Exemple2Text Ex2TextViewer)
