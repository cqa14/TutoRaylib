add_library(Ex2Dessin contenu.h dessinable.h support_a_dessin.h)
set_target_properties(Ex2Dessin PROPERTIES LINKER_LANGUAGE CXX) # Car CMake ne peut pas le deviner (.h est commun à C et C++)
target_include_directories(Ex2Dessin PUBLIC ${PROJECT_SOURCE_DIR}/SecondExemple/general)