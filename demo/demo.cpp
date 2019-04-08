#include "hippo/hippo.h"
#include <iostream>
#include <vector>

struct A {
  int a1;
  float a2;
};

struct B {
  std::vector<A> b1;
  int b2;
};

// Make A printable
HIPPO_CLASS_BEGIN(A)
HIPPO_MEMBER(a1)
HIPPO_MEMBER_EXPR(a2,
                  int(object.a2)) // custom expressions are allowed
HIPPO_CLASS_END()

// Make B printable
HIPPO_CLASS_BEGIN(B)
HIPPO_MEMBER(b1) // std::vector<A> is automatically printable because A is
HIPPO_MEMBER(b2)
HIPPO_CLASS_END()

int main() {
  B b{{{0, 1.5}, {1, 2.5}}, 3};

  std::cout << "Full:" << std::endl;
  hippo::configuration config;
  config.indent = 2;
  config.width = 0;
  std::vector<std::string> lines = hippo::print(b, config);
  for (const auto &line : lines)
    std::cout << line << std::endl;
  std::cout << std::endl;

  std::cout << "Medium condensed:" << std::endl;
  config.width = 50;
  lines = hippo::print(b, config);
  for (const auto &line : lines)
    std::cout << line << std::endl;
  std::cout << std::endl;

  std::cout << "Fully condensed:" << std::endl;
  config.width = 100;
  lines = hippo::print(b, config);
  for (const auto &line : lines)
    std::cout << line << std::endl;
  return 0;
}
