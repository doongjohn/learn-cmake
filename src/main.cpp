#include <iostream>

#include "hello.hpp"

auto main() -> int {
#ifdef HELLO
  hello();
#endif

  return 0;
}
