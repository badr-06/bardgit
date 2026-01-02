# Все исходные файлы программы
set(SOURCES
    main.cpp
    logprocess.cpp
    logprocess.h
)

# Собираем программу
add_executable(logger_app ${SOURCES})

# Подключаем библиотеку
target_link_libraries(logger_app logger_lib)