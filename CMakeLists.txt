cmake_minimum_required(VERSION 3.30.4)

set(CMAKE_CXX_STANDARD 14)

project(BitArray)

add_subdirectory(
    googletest
)

add_library(
    bitarray
    bitarray/bitarray.cpp
    bitarray/bitarray.hpp
)

add_executable(
    BitArrayTest
    test/test.cpp
)

target_link_libraries(
    BitArrayTest
    gtest
    gtest_main
    bitarray
)