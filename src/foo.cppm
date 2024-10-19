module;

#include <iostream>

export module foo;

import bar;

namespace foo {

export auto print_foo_bar() -> void {
  std::cout << "foo\n";
  bar::print_bar();
}

export auto make_bar() -> bar::Bar {
  return {};
}

} // namespace foo
