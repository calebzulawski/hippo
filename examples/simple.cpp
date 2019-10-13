#include "hippo/hippo.h"
#include "hippo/std/map.h"
#include <iostream>

struct Foo {
  int a;
  int b;
};

struct Bar {
  std::map<int, Foo> foos;
};

// Make Foo printable
HIPPO_CLASS_BEGIN(Foo)
HIPPO_MEMBER(a)
HIPPO_MEMBER(b)
HIPPO_CLASS_END()

// Make Bar printable
HIPPO_CLASS_BEGIN(Bar)
HIPPO_MEMBER(foos)
HIPPO_CLASS_END()

int main() {
  Bar bar;
  bar.foos[1] = Foo{0, 0};
  bar.foos[2] = Foo{1, 2};

  hippo::configuration config;
  config.indent = 2; // 2 spaces per indentation

  std::cout << "Expanded:" << std::endl;
  config.width = 0; // keep output as narrow as possible
  hippo::print_to(std::cout, bar, config);

  std::cout << "Condensed:" << std::endl;
  config.width = 80; // try to keep output under 80 chars
  hippo::print_to(std::cout, bar, config);
  return 0;
}
