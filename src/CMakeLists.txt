target_sources(myLib
    PUBLIC
        main.cpp
        header.h
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
        MainMenu.cpp MainMenu.h
)

target_include_directories(myLib PUBLIC ${CMAKE_CURRENT_LIST_DIR})

#add_executable(${PROJECT_NAME} myLib)
