cmake_minimum_required(VERSION 3.31)

# Generate "compile_commands.json".
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable colored output.
set(CMAKE_COLOR_DIAGNOSTICS ON)

# https://clang.llvm.org/docs/AddressSanitizer.html
set(USE_SANITIZER OFF CACHE BOOL "Use Sanitizer")

function(use_sanitizer target)
  if (USE_SANITIZER)
    message(STATUS "Setting up sanitizer for (target: ${target}, system: ${CMAKE_SYSTEM_NAME}, compiler: ${CMAKE_CXX_COMPILER_ID})")

    # Clang
    if ((CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
      if (LINUX OR APPLE OR WIN32)
        set(CMAKE_CXX_FLAGS_DEBUG "-O1")
        set(sanitizer_opts_compiler -fno-omit-frame-pointer -fno-sanitize-recover=all -fsanitize=address,undefined)
        set(sanitizer_opts_linker -fno-omit-frame-pointer -fno-sanitize-recover=all -fsanitize=address,undefined)
      endif()

      # WARNING: try catch does not work with clang address sanitizer on Windows!
      # https://github.com/google/sanitizers/issues/749
      if (WIN32)
        # Copy clang_rt.asan_dynamic-x86_64.dll
        find_package(LLVM REQUIRED CONFIG)
        add_custom_command(
          TARGET ${target} POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E copy_if_different
          "${LLVM_LIBRARY_DIRS}/clang/${LLVM_VERSION_MAJOR}/lib/windows/clang_rt.asan_dynamic-x86_64.dll"
          $<TARGET_FILE_DIR:${target}>
        )

        # clang_rt.asan_dynamic-x86_64.dll is built with /MT
        set_property(TARGET ${target} PROPERTY MSVC_RUNTIME_LIBRARY MultiThreaded$<$<CONFIG:Debug>:Debug>)
      endif()
    endif()

    # GCC
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
      if (LINUX OR APPLE)
        set(CMAKE_CXX_FLAGS_DEBUG "-O1")
        set(sanitizer_opts_compiler -fno-omit-frame-pointer -fno-sanitize-recover=all -fsanitize=address,undefined)
        set(sanitizer_opts_linker -fno-omit-frame-pointer -fno-sanitize-recover=all -fsanitize=address,undefined)
      endif()
    endif()

    # MSVC
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
      set(sanitizer_opts_compiler /fsanitize=address /Zi)
      set(sanitizer_opts_linker "")
    endif()

    # Apply sanitizer options.
    if (DEFINED sanitizer_opts_compiler AND DEFINED sanitizer_opts_linker)
      target_compile_options(${target} PRIVATE ${sanitizer_opts_compiler})
      target_link_options(${target} PRIVATE ${sanitizer_opts_linker})
    else()
      message(FATAL_ERROR "Failed to setup sanitizer for (target: ${target}, system: ${CMAKE_SYSTEM_NAME}, compiler: ${CMAKE_CXX_COMPILER_ID})")
    endif()
  endif()
endfunction()

# Prevent std version decay.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set std version.
# You can override the version for a target via set_property.
# https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html
set(CMAKE_CXX_STANDARD 20)

project(
  ExampleProject
  VERSION 0.1.0
  DESCRIPTION ""
  HOMEPAGE_URL ""
  LANGUAGES CXX
)

# Enable colored output for clang on windows.
if (WIN32 AND CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "-fdiagnostics-color=always -fansi-escape-codes")
endif()

# Link time optimization. (LTO / IPO)
# https://cmake.org/cmake/help/latest/module/CheckIPOSupported.html
if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
  include(CheckIPOSupported)
  check_ipo_supported(RESULT is_ipo_supported OUTPUT error)
  if(is_ipo_supported)
    message(STATUS "IPO enabled")
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
  else()
    message(STATUS "IPO is not supported: ${error}")
  endif()
endif()

# Create executable target.
add_executable(example-app "")
set_property(TARGET example-app PROPERTY OUTPUT_NAME "app")

use_sanitizer(example-app)

target_sources(
  example-app
  PRIVATE
    src/main.cpp
    src/hello.hpp
    src/hello.cpp
  PRIVATE
    FILE_SET CXX_MODULES FILES # C++20 modules
      src/modules/foo.cppm
      src/modules/bar.cppm
)

# target_compile_definitions(
#   example-app
#   PRIVATE
#     HELLO=1
# )

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
      # https://clang.llvm.org/docs/UsersManual.html#diagnostics-enable-everything
      -Wall
      -Wextra
  )
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # MSVC compiler options: https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category
  # MSVC linker options: https://learn.microsoft.com/en-us/cpp/build/reference/linker-options
  target_compile_options(
    example-app
    PRIVATE
      /W3
      /sdl
  )
  # target_link_options(
  #   example-app
  #   PRIVATE
  #     /VERBOSE
  # )
endif()
