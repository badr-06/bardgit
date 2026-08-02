cmake_minimum_required(VERSION 3.16)

project(MazeQt VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(SOURCES
    src/main.cpp
    src/model/maze_model.cpp
    src/model/cave_model.cpp
    src/view/main_window.cpp
    src/view/maze_widget.cpp
    src/view/cave_widget.cpp
)

set(HEADERS
    src/model/maze_model.h
    src/model/cave_model.h
    src/view/main_window.h
    src/view/maze_widget.h
    src/view/cave_widget.h
)

add_executable(maze_qt ${SOURCES} ${HEADERS})

target_link_libraries(maze_qt PRIVATE Qt6::Widgets)

target_include_directories(maze_qt PRIVATE src)

target_compile_definitions(maze_qt PRIVATE
    PROJECT_ROOT="${CMAKE_SOURCE_DIR}"
)
