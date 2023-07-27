# Learn CMake

[CMake](https://cmake.org/) is an open-source, cross-platform build file generator.

## Tutorials

- More Modern CMake\
  <https://hsf-training.github.io/hsf-training-cmake-webpage/index.html>
- CGold: The Hitchhiker’s Guide to the CMake\
  <https://cgold.readthedocs.io/en/latest/index.html>
- An Introduction to Modern CMake\
  <https://cliutils.gitlab.io/modern-cmake/>

## Usage

- generate build file:\
  <https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html>
  ```fish
  cmake -S . -B build
        [-G 'Ninja Multi-Config']
  ```
- build:
  ```fish
  cmake --build build
        [-v]
        [--config {Debug|Release|RelWithDebInfo}]
        [-t <target-name>]
  ```

## `include` & `add_subdirectory`

The most commonly used rule is "One CMakeLists.txt per target".

CMake will create a new variable scope with each `add_subdirectory()` call.

- <https://stackoverflow.com/questions/48509911/cmake-add-subdirectory-vs-include>

## `add_library`

- <https://cmake.org/cmake/help/latest/command/add_library.html>

## `FetchContent`

- <https://www.foonathan.net/2022/06/cmake-fetchcontent/>

## CPM

CPM.cmake is a cross-platform CMake script that adds dependency management capabilities to CMake. It's built as a thin wrapper around CMake's FetchContent module.

- <https://github.com/cpm-cmake/CPM.cmake>
- <https://github.com/cpm-cmake/CPM.cmake/wiki/More-Snippets>

## Cross-compilation

- [Cross Compiling With CMake](https://cmake.org/cmake/help/book/mastering-cmake/chapter/Cross%20Compiling%20With%20CMake.html)

Example of providing a toolchain file to cmake.
```cmake
# mingw.cmake

# set target operating to windows
set(CMAKE_SYSTEM_NAME Windows)

# set compiler to mingw
set(CMAKE_C_COMPILER /usr/bin/x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER /usr/bin/x86_64-w64-mingw32-windres)

# where is the target environment located
set(CMAKE_FIND_ROOT_PATH /usr/x86_64-w64-mingw32)

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
```
```fish
cmake -S . -B build_mingw -G 'Ninja Multi-Config' -DCMAKE_TOOLCHAIN_FILE=~/mingw.cmake
cmake --build build_mingw
```

