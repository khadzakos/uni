cmake_minimum_required(VERSION 3.29)
project(rb_tree)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(rb_tree
        code.cpp
        rbtree.h)
