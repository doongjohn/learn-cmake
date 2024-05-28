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

function(use_sanitizer target)
  # https://clang.llvm.org/docs/AddressSanitizer.html
  # cmake -S . -B build/windows_x64_clang_san -G "Ninja Multi-Config" -DUSE_SANITIZER:BOOL=ON
  set(USE_SANITIZER OFF CACHE BOOL "Use Sanitizer")
  if (USE_SANITIZER)
    # clang
    if ((CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
      if (LINUX OR APPLE OR WIN32)
        set(CMAKE_CXX_FLAGS_DEBUG "-O1")
        set_property(TARGET ${target} PROPERTY MSVC_RUNTIME_LIBRARY MultiThreaded)
        set(sanitizer_opts -fno-omit-frame-pointer -fno-sanitize-recover=all -fsanitize=address,undefined)
      endif()
    endif()

    # gcc
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
      if (LINUX OR APPLE)
        set(CMAKE_CXX_FLAGS_DEBUG "-O1")
        set(sanitizer_opts -fno-omit-frame-pointer -fno-sanitize-recover=all -fsanitize=address,undefined)
      endif()
    endif()

    # msvc
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
      set(CMAKE_CXX_FLAGS_DEBUG "-O1")
      get_property(msvc_rt TARGET ${target} PROPERTY MSVC_RUNTIME_LIBRARY)
      if (NOT DEFINED msvc_rt)
        set_property(TARGET ${target} PROPERTY MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>DLL)
      else()
        string(REPLACE "Debug" "" msvc_rt ${msvc_rt})
        set_property(TARGET ${target} PROPERTY MSVC_RUNTIME_LIBRARY ${msvc_rt})
      endif()
      set(sanitizer_opts /fsanitize=address /Zi)
    endif()

    if (DEFINED sanitizer_opts)
      target_compile_options(${target} PRIVATE ${sanitizer_opts})
      target_link_options(${target} PRIVATE ${sanitizer_opts})
    endif()
  endif()
endfunction()

use_sanitizer(example-app)

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
