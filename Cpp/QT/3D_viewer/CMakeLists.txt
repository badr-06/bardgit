cmake_minimum_required(VERSION 3.16)
project(3DViewer LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets OpenGLWidgets)

set(PROJECT_SOURCES
    model/matrix.h
    model/matrix.cpp
    model/figure.h
    model/figure.cpp
    model/file_parser.cpp
    model/file_parser.h
    model/file_ready.h
    model/file_ready.cpp
    model/model.h
    model/model.cpp
    controller/controller.h
    controller/controller.cpp
    view/view.h
    view/view.cpp
    view/openGL.h
    view/openGL.cpp
    info.h
)

add_executable(3DViewer
    ${PROJECT_SOURCES}
)

target_link_libraries(3DViewer
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt::OpenGLWidgets
)
