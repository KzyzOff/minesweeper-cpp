cmake_minimum_required(VERSION 3.21)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")

set(CMAKE_GENERATOR "Ninja")

add_compile_options(-Wall -Wextra -pedantic)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_library(myLib "")
add_subdirectory(src)

add_executable(${PROJECT_NAME})#main.cpp
        #[[header.h
        CONSTANTS.h
        Color.h
        common.h
        App.cpp App.h
        MinesweeperCore.cpp MinesweeperCore.h
        BoardView.cpp BoardView.h
        FontManager.cpp FontManager.h
        Clock.cpp Clock.h
        Controller.h
        BoardController.cpp BoardController.h
        Button.h Button.cpp
        MainMenu.cpp MainMenu.h)]]

target_link_libraries(${PROJECT_NAME} myLib SDL2::Main SDL2::Image SDL2::TTF)
