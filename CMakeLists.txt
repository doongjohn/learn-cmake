cmake_minimum_required(VERSION 3.27)

# generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# enable colored output
set(CMAKE_COLOR_DIAGNOSTICS ON)

project(
  ExampleProject
  VERSION 0.1.0
  DESCRIPTION ""
  HOMEPAGE_URL ""
  LANGUAGES CXX
)

# enable colored output
if (WIN32 AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "-fdiagnostics-color=always -fansi-escape-codes")
endif()

add_executable(example-app "")

# https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html
set_property(TARGET example-app PROPERTY OUTPUT_NAME "app")
set_property(TARGET example-app PROPERTY CXX_STANDARD 20)

# enable sanitizers for clang
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS_DEBUG "-O1") # https://clang.llvm.org/docs/AddressSanitizer.html#id3
  if (WIN32)
    set_property(TARGET example-app PROPERTY MSVC_RUNTIME_LIBRARY $<$<CONFIG:Debug>:MultiThreaded>)
  endif()
  set(SANITIZER_OPT $<$<CONFIG:Debug>:-fno-omit-frame-pointer -fno-sanitize-recover=all -fsanitize=address,undefined>)
  target_compile_options(example-app PRIVATE ${SANITIZER_OPT})
  target_link_options(example-app PRIVATE ${SANITIZER_OPT})
endif()

# enable sanitizers for gcc
if (NOT WIN32 AND CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  set(CMAKE_CXX_FLAGS_DEBUG "-O1")
  set(SANITIZER_OPT $<$<CONFIG:Debug>:-fno-omit-frame-pointer -fno-sanitize-recover=all -fsanitize=address,undefined>)
  target_compile_options(example-app PRIVATE ${SANITIZER_OPT})
  target_link_options(example-app PRIVATE ${SANITIZER_OPT})
endif()

# target_compile_definitions(
#   example-app
#   PRIVATE
#     HELLO=1
# )

target_sources(
  example-app
  PRIVATE
    src/main.cpp
    src/hello.cpp
)

# target_include_directories(
#   example-app
#   PRIVATE
#     ${PROJECT_SOURCE_DIR}/include
# )

# target_link_libraries(
#   example-app
#   PRIVATE
#     library_name
# )

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(
    example-app
    PRIVATE
      -Wall
      -Wextra
  )
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # msvc compiler options: https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category
  target_compile_options(
    example-app
    PRIVATE
      /Wall
      /sdl
  )
  # msvc linker options: https://learn.microsoft.com/en-us/cpp/build/reference/linker-options
  # target_link_options(
  #   example-app
  #   PRIVATE
  #     /VERBOSE
  # )
endif()
