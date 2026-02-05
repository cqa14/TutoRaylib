add_library(Ex3Dessin contenu.h dessinable.h support_a_dessin.h)
target_include_directories(Ex3Dessin PUBLIC ${PROJECT_SOURCE_DIR}/TroisiemeExemple/general)
target_compile_options(Ex3Dessin PRIVATE ${PROJECT_WARNING_FLAGS})
set_target_properties(Ex3Dessin PROPERTIES LINKER_LANGUAGE CXX) # Car CMake ne peut pas le deviner (.h est commun à C et C++)
