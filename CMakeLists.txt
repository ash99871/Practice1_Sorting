cmake_minimum_required(VERSION 4.0)
project(Sorting)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Sorting
        avlTree.cpp
        avlTree.h
        heapSort.cpp
        heapSort.h
        main.cpp
        medidor.h
        quickSort.cpp
        quickSort.h)
