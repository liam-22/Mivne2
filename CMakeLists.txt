cmake_minimum_required(VERSION 3.7)
project(Mivne2Wet)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp SplayTree.h Gladiator.cpp Gladiator.h Exceptions.h cmake-build-debug/Heap.cpp cmake-build-debug/Heap.h)
add_executable(Mivne2Wet ${SOURCE_FILES})