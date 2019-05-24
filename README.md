# Hippo (Hierarchical Information Pretty-Printer Objects)

Support for:
* Custom type printers via reflection macros (`class`/`struct` and `enum`/`enum class`)
* Builtin types
  * Arithmetic types (i.e. `std::is_arithmetic_v<T> == true`)
  * C-style arrays (e.g. `int [10]`)
* Strings (`std::string`, `const char *`)
* Containers:
  * `std::array`
  * `std::vector`
  * `std::list`, `std::forward_list`
  * `std::deque`
  * `std::set`, `std::multiset`, `std::unordered_set`, `std::unordered_multiset`
  * `std::map`, `std::multimap`, `std::unordered_map`, `std::unordered_multimap`
* `std::optional`, `std::variant`
  
## Defining a custom type printer
Custom class types can be made printable with the reflection helper macros `HIPPO_CLASS_BEGIN`, `HIPPO_MEMBER`, `HIPPO_MEMBER_EXPR`, and `HIPPO_CLASS_END`.
Enums can be made printable with the similar `HIPPO_ENUM_BEGIN`, `HIPPO_ENUM_VALUE`, and `HIPPO_ENUM_END` macros.
The following is copied from `test/demo.cpp`
```c++
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
HIPPO_MEMBER_EXPR(a2, int(object.a2)) // custom expressions are allowed
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
```

When run, this program produces:
```
Full:
B {
  b1: std::vector [
    A {
      a1: 0,
      a2: 1
    },
    A {
      a1: 1,
      a2: 2
    }
  ],
  b2: 3
}

Medium condensed:
B {
  b1: std::vector [
    A { a1: 0, a2: 1 },
    A { a1: 1, a2: 2 }
  ],
  b2: 3
}

Fully condensed:
B { b1: std::vector [ A { a1: 0, a2: 1 }, A { a1: 1, a2: 2 } ], b2: 3 }
```
