module;

#include <iostream>

export module foo;

namespace foo {

export auto print_foo() -> void {
  std::cout << "foo\n";
}

}
