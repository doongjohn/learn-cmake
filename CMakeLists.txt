cmake_minimum_required(VERSION 3.27)

set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  LearnCMake
  VERSION 0.1.0
  DESCRIPTION ""
  HOMEPAGE_URL ""
  LANGUAGES CXX
)

add_executable(example-app "")

set_target_properties(${target}
  PROPERTIES # https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html
  # EXCLUDE_FROM_ALL true
  OUTPUT_NAME ${output_name})

target_compile_features(${target}
  PRIVATE cxx_std_20)

# enable sanitizers
if (NOT WIN32 AND CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  set(SANITIZER_OPTIONS
    $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
    $<$<CONFIG:Debug>:-fno-sanitize-recover=all>
    $<$<CONFIG:Debug>:-fsanitize=address,undefined>)

  target_compile_options(${target}
    PRIVATE ${SANITIZER_OPTIONS})

  target_link_options(${target}
    PRIVATE ${SANITIZER_OPTIONS})
endif()

# target_compile_definitions(example-app
#   PRIVATE HELLO=1)

target_sources(example-app
  PRIVATE src/main.cpp)

# target_include_directories(example-app
#   PRIVATE ${PROJECT_SOURCE_DIR}/include)

# target_link_libraries(example-app
#   library_name)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(example-app
    # more warnings
    PRIVATE -Wall
    PRIVATE -Wextra)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # msvc compiler options: https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category
  target_compile_options(example-app
    # more warnings
    PRIVATE /Wall
    PRIVATE /sdl)

  # msvc linker options: https://learn.microsoft.com/en-us/cpp/build/reference/linker-options
  # target_link_options(example-app
  #   PRIVATE
  #     /VERBOSE)
endif()
