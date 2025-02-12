cmake_minimum_required(VERSION 3.29)
project(b_tree)

set(CMAKE_CXX_STANDARD 20)

add_executable(b_tree main.cpp btree.h btree.cpp)
