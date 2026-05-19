cmake_minimum_required(VERSION 3.25)
project(algo_tree_processing C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab1
        lab1/main.c
        lab1/tree.c
)

add_executable(lab1_tests
        lab1/tests.c
        lab1/tree.c
)

add_executable(lab2
        lab2/main.c
        lab2/table.c
)

add_executable(lab2_tests
        lab2/tests.c
        lab2/table.c
)

add_executable(lab3
        lab3/main.c
        lab3/tree.c
        lab3/stacks.c
        lab3/parser.c
)

add_executable(lab3_tests
        lab3/tests.c
        lab3/tree.c
        lab3/stacks.c
        lab3/parser.c
)

add_executable(lab4
        lab4/main.c
        lab4/avlTree.c
)

add_executable(lab4_tests
        lab4/tests.c
        lab4/avlTree.c
)

add_library(lab5_lib
        lab5/graph.c
        lab5/floyd.c
        lab5/result.c
)

target_include_directories(lab5_lib PUBLIC lab5)

add_executable(lab5
        lab5/main.c
)

target_link_libraries(lab5 PRIVATE lab5_lib)

enable_testing()

if(EXISTS "${CMAKE_SOURCE_DIR}/third_party/googletest/CMakeLists.txt")
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        add_subdirectory(third_party/googletest EXCLUDE_FROM_ALL)

        add_executable(lab5_tests
                lab5/tests.cpp
        )

        target_link_libraries(lab5_tests PRIVATE lab5_lib GTest::gtest_main)

        include(GoogleTest)
        gtest_discover_tests(lab5_tests)
else()
        find_package(GTest QUIET)
        if(GTest_FOUND)
                add_executable(lab5_tests
                        lab5/tests.cpp
                )

                target_link_libraries(lab5_tests PRIVATE lab5_lib GTest::gtest_main)

                include(GoogleTest)
                gtest_discover_tests(lab5_tests)
        else()
                message(STATUS "GTest not found: lab5_tests target is disabled")
        endif()
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/third_party/benchmark/CMakeLists.txt")
        set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
        set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
        set(BENCHMARK_ENABLE_WERROR OFF CACHE BOOL "" FORCE)
        add_subdirectory(third_party/benchmark EXCLUDE_FROM_ALL)

        add_executable(lab5_benchmark
                lab5/benchmark.cpp
        )

        target_link_libraries(lab5_benchmark PRIVATE lab5_lib benchmark::benchmark)
else()
        find_package(benchmark QUIET CONFIG)
        if(benchmark_FOUND)
                add_executable(lab5_benchmark
                        lab5/benchmark.cpp
                )

                target_link_libraries(lab5_benchmark PRIVATE lab5_lib benchmark::benchmark)
        else()
                message(STATUS "Google Benchmark not found: lab5_benchmark target is disabled")
        endif()
endif()
