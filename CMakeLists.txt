cmake_minimum_required(VERSION 3.15..3.20)

project(
  aoc
  VERSION 0.1.0
  LANGUAGES CXX)

add_compile_options(-std=c++17 -Wall -Wextra -Wpedantic -Werror)

add_subdirectory(src)
add_subdirectory(apps)
