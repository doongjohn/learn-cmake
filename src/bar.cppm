module;

#include <iostream>

export module bar;

namespace bar {

export struct Bar {
  std::string str = "bar";
};

export auto print_bar() -> void {
  std::cout << "bar\n";
}

} // namespace bar
