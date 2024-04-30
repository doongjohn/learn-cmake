#include <cstdlib>
#include <format>
#include <iostream>

#ifdef HELLO
#include "hello.hpp"
#endif

auto main() -> int {
  const auto cmake = "CMake";
  std::cout << std::format("Built with {}\n", cmake);

#ifdef HELLO
  hello();
#endif

  return EXIT_SUCCESS;
}
