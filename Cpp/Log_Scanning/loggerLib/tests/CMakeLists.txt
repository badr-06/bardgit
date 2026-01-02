# Минимальная требуемая версия CMake (для совместимости)
cmake_minimum_required(VERSION 3.16)

# Название проекта для тестов (используется в логах сборки)
project(LoggerTests)

# Поиск и подключение библиотеки Google Test
find_package(GTest REQUIRED)

# Указываем исходный файл с тестами (полный путь)
set(TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)

# Создаем исполняемый файл для тестов
add_executable(logger_tests ${TEST_SOURCES})

# Подключаем зависимости:
# - Нашу библиотеку логгера
# - Основную библиотеку GTest
# - Main-функцию GTest
target_link_libraries(logger_tests
    logger_lib
    GTest::GTest
    GTest::Main
)

# Добавляем пути к заголовочным файлам:
target_include_directories(logger_tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../library/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
)

# Регистрируем тест в CTest (для запуска через 'ctest')
add_test(NAME logger_tests COMMAND logger_tests)