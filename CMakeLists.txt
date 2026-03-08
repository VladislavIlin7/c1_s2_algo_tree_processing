cmake_minimum_required(VERSION 3.25)
project(algo_tree_processing C)

set(CMAKE_C_STANDARD 11)

add_executable(lab1
        lab1/main.c
        lab1/tree.c
        lab1/tests.c
        lab2/table.c
)

add_executable(lab2
        lab2/main.c
        lab2/table.c
        lab2/tests.c
        lab2/table.c
)