#include <format>
#include <iostream>

#ifdef HELLO
#include "hello.hpp"
#endif

auto main() -> int {
  const auto str = std::string("C++");
  std::cout << std::format("This is {} {}\n", str, 20);

#ifdef HELLO
  hello();
#endif

  return 0;
}
