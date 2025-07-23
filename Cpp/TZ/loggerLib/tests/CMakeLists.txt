cmake_minimum_required(VERSION 3.16)
project(LoggerTests)

find_package(GTest REQUIRED)

set(TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)  # Полный путь к файлу

add_executable(logger_tests ${TEST_SOURCES})

target_link_libraries(logger_tests
    logger_lib
    GTest::GTest
    GTest::Main
)

target_include_directories(logger_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../library/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

add_test(NAME logger_tests COMMAND logger_tests)