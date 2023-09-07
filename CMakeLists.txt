cmake_minimum_required(VERSION 3.25)

# generate `compile_commands.json` (only for make and ninja)
# ln -s build/compile_commands.json compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable colored output for GNU/Clang compilers
set(CMAKE_COLOR_DIAGNOSTICS ON)

project(
  ExampleProject
  VERSION 0.1.0
  DESCRIPTION ""
  HOMEPAGE_URL ""
  LANGUAGES CXX
)

add_executable(example-app "")

set_target_properties(example-app
  PROPERTIES # https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html
  # EXCLUDE_FROM_ALL true
  OUTPUT_NAME app)

target_compile_features(example-app
  PRIVATE cxx_std_20)

# target_compile_definitions(example-app
#   PRIVATE HELLO=1)

# https://crascit.com/2016/01/31/enhanced-source-file-handling-with-target_sources/
file(GLOB_RECURSE SRC_FILES
  src/*.cpp
  src/*.hpp)
target_sources(example-app
  PRIVATE ${SRC_FILES})

# target_include_directories(example-app
#   PRIVATE ${PROJECT_SOURCE_DIR}/include)

# target_link_libraries(example-app
#   library_name)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(example-app
    PRIVATE
      # more warnings
      -Wall -Wextra)

  if (NOT WIN32)
    # use sanitizers
    set(SANITIZER_OPTIONS
      $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
      $<$<CONFIG:Debug>:-fno-sanitize-recover=all>
      $<$<CONFIG:Debug>:-fsanitize=address,undefined>)
    target_compile_options(example-app
      PRIVATE ${SANITIZER_OPTIONS})
    target_link_options(example-app
      PRIVATE ${SANITIZER_OPTIONS})
  endif()
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # msvc compiler options: https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category
  target_compile_options(example-app
    PRIVATE
      # more warnings
      /W4 /sdl)

  # msvc linker options: https://learn.microsoft.com/en-us/cpp/build/reference/linker-options
  # target_link_options(example-app
  #   PRIVATE
  #     /VERBOSE)
endif()
