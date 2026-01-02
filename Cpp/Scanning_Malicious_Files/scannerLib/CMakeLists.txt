set(SCANNERLIB_SOURCES
    FileScanner.cpp
    HashDatbase.cpp
    Logger.cpp
)

add_library(scannerLib ${SCANNERLIB_SOURCES})
target_include_directories(scannerLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# OpenSSL кроссплатформенно
find_package(OpenSSL REQUIRED)
target_link_libraries(scannerLib PUBLIC OpenSSL::SSL OpenSSL::Crypto)

# Потоки: используем стандартный C++ или system libs
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(scannerLib PUBLIC ws2_32)
elseif (UNIX)
    find_package(Threads REQUIRED)
    target_link_libraries(scannerLib PUBLIC Threads::Threads)
endif()
