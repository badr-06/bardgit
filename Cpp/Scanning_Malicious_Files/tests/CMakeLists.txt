find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE scannerLib GTest::gtest GTest::gtest_main Threads::Threads)
enable_testing()
add_test(NAME FileScanTests COMMAND tests)