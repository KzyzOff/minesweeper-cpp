cmake_minimum_required(VERSION 3.21)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 14)

include_directories("/usr/include/SDL2")

add_executable(${PROJECT_NAME} main.cpp
        App.cpp App.h
        MinesweeperCore2D.cpp MinesweeperCore2D.h
        BoardView.cpp BoardView.h
        FontManager.cpp FontManager.h
#        AppState.h
        Clock.cpp Clock.h
#        MinesweeperCore1D.cpp MinesweeperCore1D.h
        )

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})
