cmake_minimum_required(VERSION 3.21)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
add_compile_options(-Wall -Wextra -pedantic)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

if (MINGW)
    set (CMAKE_HOST_SYSTEM "Windows")
    set (CMAKE_SYSTEM_PROCESSOR "x86")
    set (CMAKE_SYSTEM_VERSION "6.1")

    set (SDL2_STATIC_LIBRARIES TRUE)
    set (SDL2_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/sdl2/x86_64-w64-mingw32/lib/cmake/SDL2)
    set (SDL2IMAGE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/sdl2_image/x86_64-w64-mingw32/lib/pkgconfig)
    set (SDL2TTF_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libraries/sdl2_ttf/x86_64-w64-mingw32/lib/pkgconfig)
endif (MINGW)

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
        MainMenu.cpp MainMenu.h header.h)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::Image SDL2::TTF)
