add_library(Ex6Dessin contenu.h dessinable.h support_a_dessin.h)
set_target_properties(Ex6Dessin PROPERTIES LINKER_LANGUAGE CXX) # Car CMake ne peut pas le deviner (.h est commun à C et C++)
target_include_directories(Ex6Dessin PUBLIC ${PROJECT_SOURCE_DIR}/SixiemeExemple/general)