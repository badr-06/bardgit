option(BUILD_SHARED_LIBS "Собирать как динамическую библиотеку" OFF)

set(SOURCES 
    src/logger.cpp
    ../src/logprocess.cpp  # Добавляем реализацию logProcessor
    include/logger.h
    ../src/logprocess.h   # Добавляем заголовок logProcessor
)

if(BUILD_SHARED_LIBS)
    add_library(logger_lib SHARED ${SOURCES})
    message(STATUS "Собираем динамическую библиотеку")
else()
    add_library(logger_lib STATIC ${SOURCES})
    message(STATUS "Собираем статическую библиотеку")
endif()

target_include_directories(logger_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../src  # Добавляем путь к logprocess.h
)