#include <iostream>
#include <string>

#include "linenoise.hpp"
#include "hello.hpp"

using std::string;

int main() {
  hello();

  while (true) {
    // Read line
    string line;
    auto quit = linenoise::Readline("hello> ", line);

    if (quit) {
      break;
    }

    std::cout <<  "echo: '" << line << "'" << std::endl;

    // Add text to history
    linenoise::AddHistory(line.c_str());
  }

  return 0;
}
