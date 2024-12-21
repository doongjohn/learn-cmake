module;

#include <iostream>

export module foo;

import bar;

namespace foo {

export auto hello_foobar() -> void {
  std::cout << "hello from foo\n";
  bar::hello_bar();
}

export auto make_bar() -> bar::Bar {
  return {};
}

} // namespace foo
