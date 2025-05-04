cmake_minimum_required(VERSION 3.21)
project(TutoRaylib)
set(CMAKE_CXX_STANDARD 20)

####################################################################
# Installation de raylib si nécessaire

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        FetchContent_MakeAvailable(raylib)
    endif ()
endif ()

# Optionnel : installation de raygui
FetchContent_Declare(
        raygui
        GIT_REPOSITORY "https://github.com/raysan5/raygui.git"
        GIT_TAG "4.0"
        GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raygui)

####################################################################
# Ajout des exemples
add_subdirectory(HelloWorld)
add_subdirectory(PremierExemple)
add_subdirectory(SecondExemple)
add_subdirectory(TroisiemeExemple)
add_subdirectory(QuatriemeExemple)
add_subdirectory(CinquiemeExemple)
add_subdirectory(SixiemeExemple)
