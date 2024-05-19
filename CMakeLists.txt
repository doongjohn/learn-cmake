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
)

# enable colored output
if (WIN32 AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "-fdiagnostics-color=always -fansi-escape-codes")
endif()

add_executable(example-app "")

# https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html
set_property(TARGET example-app PROPERTY OUTPUT_NAME "app")
set_property(TARGET example-app PROPERTY CXX_STANDARD 20)
set_property(TARGET example-app PROPERTY MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>)

# https://clang.llvm.org/docs/AddressSanitizer.html
# cmake -S . -B build/windows_x64_clang_san -G "Ninja Multi-Config" -DUSE_SANITIZER:BOOL=true
set(USE_SANITIZER false CACHE BOOL "Use Sanitizer")
if (USE_SANITIZER)
  # clang
  if ((CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    set(CMAKE_CXX_FLAGS_DEBUG "-O1")
    if (LINUX)
      set(SANITIZER_OPTS -fno-omit-frame-pointer -fno-sanitize-recover=all -fsanitize=memory,address,undefined)
    endif()
    if (APPLE)
      set(SANITIZER_OPTS -fno-omit-frame-pointer -fno-sanitize-recover=all -fsanitize=address,undefined)
    endif()
    if (WIN32)
      set(SANITIZER_OPTS -fno-omit-frame-pointer -fno-sanitize-recover=all -fsanitize=address,undefined)
    endif()
  endif()

  # gcc
  if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "-O1")
    if (LINUX)
      set(SANITIZER_OPTS -fno-omit-frame-pointer -fno-sanitize-recover=all -fsanitize=memory,address,undefined)
    endif()
    if (APPLE)
      set(SANITIZER_OPTS -fno-omit-frame-pointer -fno-sanitize-recover=all -fsanitize=address,undefined)
    endif()
  endif()

  # msvc
  if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CMAKE_CXX_FLAGS_DEBUG "-O1")
    set(SANITIZER_OPTS /fsanitize=address /Zi)
  endif()

  if (DEFINED SANITIZER_OPTS)
    set_property(TARGET example-app PROPERTY MSVC_RUNTIME_LIBRARY MultiThreaded)
    target_compile_options(example-app PRIVATE ${SANITIZER_OPTS})
    target_link_options(example-app PRIVATE ${SANITIZER_OPTS})
    unset(SANITIZER_OPTS)
  endif()
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
      /W3
      /sdl
  )
  # msvc linker options: https://learn.microsoft.com/en-us/cpp/build/reference/linker-options
  # target_link_options(
  #   example-app
  #   PRIVATE
  #     /VERBOSE
  # )
endif()
