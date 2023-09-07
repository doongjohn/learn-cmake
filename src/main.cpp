#include <format>
#include <iostream>

#include "hello.hpp"

auto main() -> int {
  std::cout << std::format("This is {} {}\n", "C++", 20);

#ifdef HELLO
  hello();
#endif

  return 0;
}
