cmake_minimum_required(VERSION 3.16)

project(aoc_day_seven VERSION 0.1.0)

add_executable(part_one src/part_one.cc)
add_executable(part_two src/part_two.cc)

# Optionally, add options for building tests, examples, etc.
option(BUILD_TESTS "Build tests" OFF)
if (BUILD_TESTS)
    enable_testing()  # Enables CTest, which is included with CMake
    add_subdirectory(tests)
endif ()
