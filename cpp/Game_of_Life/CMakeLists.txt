cmake_minimum_required(VERSION 3.14)
project(GameOfLife)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
)

add_executable(GameOfLife ${SOURCES})

find_package(SDL2 REQUIRED)

if (SDL2_FOUND)
    target_include_directories(GameOfLife PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(GameOfLife PRIVATE ${SDL2_LIBRARIES})
else()
    message(FATAL_ERROR "Не найдена библиотека SDL2!")
endif()

set_target_properties(GameOfLife PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
