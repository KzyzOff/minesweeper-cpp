cmake_minimum_required(VERSION 3.21)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 14)

include_directories("/usr/include/SDL2")

#include(kiss_sdl/CMakeLists.txt)
#add_library(kiss)
#add_subdirectory(kiss_sdl)

add_executable(${PROJECT_NAME} main.cpp
        common.h
        CONSTANTS.h
        App.cpp App.h
        MinesweeperCore.cpp MinesweeperCore.h
        BoardView.cpp BoardView.h
        FontManager.cpp FontManager.h
        Clock.cpp Clock.h
        Color.h
        Controller.h
        BoardController.cpp BoardController.h
        Button.h Button.cpp
        MainMenu.cpp MainMenu.h)

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})
