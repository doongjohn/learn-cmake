#include <cstdlib>
#include <format>
#include <iostream>

#ifdef HELLO
#include "hello.hpp"
#endif

auto main() -> int {
  const auto str = "CMake";
  std::cout << std::format("Built with {}\n", str);

#ifdef HELLO
  hello();
#endif

  return EXIT_SUCCESS;
}
