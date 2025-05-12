add_library(Ex2TextViewer text_viewer.h text_viewer.cpp)
target_link_libraries(Ex2TextViewer Ex2Dessin)

add_executable(Exemple2Text main_text.cpp)
target_link_libraries(Exemple2Text Ex2TextViewer)