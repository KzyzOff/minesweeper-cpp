cmake_minimum_required(VERSION 3.21)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O2")
add_compile_options(-Wall -Wextra -pedantic)

#if(WIN32)
#    set(SDL2_DIR "../external/sdl2/")
#    set(SDL2_IMAGE_DIR "../external/sdl2_image/")
#    set(SDL2_TTF_DIR "../external/sdl2_ttf")
#endif(WIN32)

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

#include(FindPkgConfig)

#pkg_search_module(SDL2 REQUIRED sdl2)
#pkg_search_module(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
#pkg_search_module(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

#find_package(SDL2 REQUIRED sdl2)
#find_package(SDL2IMAGE REQUIRED SDL2_image)
#find_package(SDL2TTF REQUIRED SDL2_ttf)

include_directories("${PROJECT_SOURCE_DIR}/dlls")
add_subdirectory(dlls)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})
