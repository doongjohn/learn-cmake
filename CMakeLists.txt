cmake_minimum_required(VERSION 3.24)

# 1. setup cmake
# cmake -S . -B build -G generator
# 2. build
# cmake --build build

# common problems in cmake
# https://hsf-training.github.io/hsf-training-cmake-webpage/07-commonproblems/index.html

# set(HI "hello world")
# message(STATUS "${HI}")

project(
  HelloWorld
  LANGUAGES CXX
)

# learn more about package

# learn more about add_subdirectory
# https://stackoverflow.com/questions/48509911/cmake-add-subdirectory-vs-include

# https://stackoverflow.com/questions/59263015/cmake-how-to-change-compile-commands-json-output-location
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(linenoise INTERFACE)
target_include_directories(
  linenoise
  INTERFACE
    vendor/cpp-linenoise
)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(hello ${SRC_FILES})
target_compile_features(
  hello
  PRIVATE cxx_std_20
)
target_link_libraries(
  hello
  linenoise
)
