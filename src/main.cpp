#include <cstdlib>
#include <format>
#include <iostream>

#ifdef HELLO
#include "hello.hpp"
#endif

import foo;

auto main() -> int {
  const auto str = std::string{"CMake"};
  std::cout << std::format("Built with {}\n", str);

#ifdef HELLO
  hello();
#endif

  foo::print_foo();

  return EXIT_SUCCESS;
}
