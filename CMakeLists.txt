cmake_minimum_required(VERSION 3.25)

# generate `compile_commands.json` (only for make and ninja)
# ln -s build/compile_commands.json compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  ExampleProject
  VERSION 0.1.0
  DESCRIPTION ""
  HOMEPAGE_URL ""
  LANGUAGES CXX
)

add_executable(exmple-app "")

set_target_properties(exmple-app
  PROPERTIES # https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html
  # EXCLUDE_FROM_ALL true
  OUTPUT_NAME app)

target_compile_features(exmple-app
  PRIVATE cxx_std_20)

target_compile_definitions(exmple-app
  PRIVATE HELLO=1)

# https://crascit.com/2016/01/31/enhanced-source-file-handling-with-target_sources/
file(GLOB_RECURSE SRC_FILES
  src/*.cpp
  src/*.hpp)
target_sources(exmple-app
  PRIVATE ${SRC_FILES})

# target_include_directories(exmple-app
#   PRIVATE ${PROJECT_SOURCE_DIR}/include)

# target_link_libraries(exmple-app
#   library_name)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(exmple-app
    PRIVATE
      # use colored output
      $<$<C_COMPILER_ID:GNU>:-fdiagnostics-color>
      $<$<C_COMPILER_ID:Clang>:-fcolor-diagnostics>
      $<$<CXX_COMPILER_ID:GNU>:-fdiagnostics-color>
      $<$<CXX_COMPILER_ID:Clang>:-fcolor-diagnostics>
      # more warnings
      -Wall)

  # use sanitizers
  if (NOT WIN32)
    target_compile_options(exmple-app
      PRIVATE
        $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
        $<$<CONFIG:Debug>:-fno-sanitize-recover=all>
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>)
    target_link_options(exmple-app
      PRIVATE
        $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
        $<$<CONFIG:Debug>:-fno-sanitize-recover=all>
        $<$<CONFIG:Debug>:-fsanitize=address,undefined>)
  endif()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # msvc compiler options: https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category
  target_compile_options(exmple-app
    PRIVATE
      # more warnings
      /W4 /sdl)

  # msvc linker options: https://learn.microsoft.com/en-us/cpp/build/reference/linker-options
  target_link_options(exmple-app
    PRIVATE
      /VERBOSE)
endif()
