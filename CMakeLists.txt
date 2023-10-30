cmake_minimum_required(VERSION 3.27)

# generate `compile_commands.json` (only for make and ninja)
# ln -s build/compile_commands.json compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable colored output for GNU/Clang compilers
set(CMAKE_COLOR_DIAGNOSTICS ON)

project(
  LearnCMake
  VERSION 0.1.0
  DESCRIPTION ""
  HOMEPAGE_URL ""
  LANGUAGES CXX
)

function(setup_target_cxx_20 target output_name)
  set_target_properties(${target}
    PROPERTIES # https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html
    # EXCLUDE_FROM_ALL true
    OUTPUT_NAME ${output_name})

  target_compile_features(${target}
    PRIVATE cxx_std_20)

  # https://crascit.com/2016/01/31/enhanced-source-file-handling-with-target_sources/
  file(GLOB_RECURSE SOURCES src/*.cpp src/*.hpp)
  target_sources(${target} PRIVATE ${SOURCES})

  # enable sanitizers
  if (NOT WIN32 AND CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    set(SANITIZER_OPTIONS
      $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
      $<$<CONFIG:Debug>:-fno-sanitize-recover=all>
      $<$<CONFIG:Debug>:-fsanitize=address,undefined>)
    target_compile_options(example-app PRIVATE ${SANITIZER_OPTIONS})
    target_link_options(example-app PRIVATE ${SANITIZER_OPTIONS})
  endif()
endfunction()

add_executable(example-app "")
setup_target_cxx_20(example-app app)

# target_include_directories(example-app
#   PRIVATE ${PROJECT_SOURCE_DIR}/include)

# target_compile_definitions(example-app
#   PRIVATE HELLO=1)

# target_link_libraries(example-app
#   library_name)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
  target_compile_options(example-app
    PRIVATE
      # more warnings
      -Wall -Wextra)

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # msvc compiler options: https://learn.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category
  target_compile_options(example-app
    PRIVATE
      # more warnings
      /Wall /sdl)

  # msvc linker options: https://learn.microsoft.com/en-us/cpp/build/reference/linker-options
  # target_link_options(example-app
  #   PRIVATE
  #     /VERBOSE)
endif()
