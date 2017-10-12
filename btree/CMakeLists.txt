cmake_minimum_required(VERSION 3.7)
project(btree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        btree.h
        btree_iterator.h
        test03.cpp
        twl.txt
        twl1.txt)

add_executable(btree ${SOURCE_FILES})