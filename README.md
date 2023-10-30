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

- Generate build file:\
  <https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html>
  ```fish
  cmake -S . -B <build-dir>
        [-G {"Ninja Multi-Config"|"Visual Studio 17 2022"}]
  ```
- Build:
  ```fish
  cmake --build <build-dir>
        [-v]
        [--config {Debug|Release|RelWithDebInfo}]
        [-t <target-name>]
        [-j <max-parallel-jobs>]
  ```
- 32/64bit build
    - **GCC and Clang:** (compiler and linker flag)
        - 32bit: `-m32`
        - 64bit: `-m64`
    - **MSVC:**
        - 32bit: `cmake ... -G ... -A Win32`
        - 64bit: `cmake ... -G ... -A x64`
- Convert MinGW `*.dll.a` to `*.dll`\
  `set(CMAKE_GNUtoMS ON)`\
  <https://cmake.org/cmake/help/latest/variable/CMAKE_GNUtoMS.html>
- Configure portable parallel builds\
  <https://stackoverflow.com/a/70102570>
- Overriding a default option(...) value from a parent CMakeLists.txt\
  <https://stackoverflow.com/q/3766740>

### `message`

- <https://cmake.org/cmake/help/latest/command/message.html>

#### General messages

`message([<mode>] "message text" ...)`

Record the specified message text in the log. If more than one message string is given, they are concatenated into a single message with no separator between the strings.

The optional `<mode>` keyword determines the type of message, which influences the way the message is handled:

- FATAL_ERROR
- SEND_ERROR
- WARNING
- AUTHOR_WARNING
- DEPRECATION
- NOTICE (default)
- STATUS
- VERBOSE
- DEBUG
- TRACE

#### Reporting checks

A common pattern in CMake output is a message indicating the start of some sort of check, followed by another message reporting the result of that check.

`message(<checkState> "message" ...)`

where <checkState> must be one of the following:

- CHECK_START\
    Record a concise message about the check about to be performed.
- CHECK_PASS\
    Record a successful result for a check.
- CHECK_FAIL\
    Record an unsuccessful result for a check.

Checks may be nested and every CHECK_START should have exactly one matching CHECK_PASS or CHECK_FAIL. The CMAKE_MESSAGE_INDENT variable can also be used to add indenting to nested checks if desired. For example:

```cmake
message(CHECK_START "Finding my things")
list(APPEND CMAKE_MESSAGE_INDENT "  ")
unset(missingComponents)

message(CHECK_START "Finding partA")
# ... do check, assume we find A
message(CHECK_PASS "found")

message(CHECK_START "Finding partB")
# ... do check, assume we don't find B
list(APPEND missingComponents B)
message(CHECK_FAIL "not found")

list(POP_BACK CMAKE_MESSAGE_INDENT)
if(missingComponents)
  message(CHECK_FAIL "missing components: ${missingComponents}")
else()
  message(CHECK_PASS "all components found")
endif()
```

Output from the above would appear something like the following:

```
-- Finding my things
--   Finding partA
--   Finding partA - found
--   Finding partB
--   Finding partB - not found
-- Finding my things - missing components: B
```

### `include` & `add_subdirectory`

The most commonly used rule is "One CMakeLists.txt per target".\
CMake will create a new variable scope with each `add_subdirectory()` call.

- <https://stackoverflow.com/questions/48509911/cmake-add-subdirectory-vs-include>

### `add_library`

- <https://cmake.org/cmake/help/latest/command/add_library.html>

### `FetchContent`

- <https://cmake.org/cmake/help/latest/module/FetchContent.html>
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

