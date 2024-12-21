module;

#include <iostream>

export module bar;

namespace bar {

export struct Bar {
  std::string str = "bar";

  auto print() -> void {
    std::cout << str;
  }
};

export auto hello_bar() -> void {
  std::cout << "hello from bar\n";
}

} // namespace bar
