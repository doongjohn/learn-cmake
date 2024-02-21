#include <format>
#include <iostream>

#ifdef HELLO
#include "hello.hpp"
#endif

template <class... T>
auto format_print(const std::format_string<T...> fmt, T &&...args) -> void {
  std::cout << std::format(fmt, args...);
}

auto main() -> int {
  const auto str = std::string{"CMake"};
  format_print("Built with {}\n", str);

#ifdef HELLO
  hello();
#endif

  return 0;
}
