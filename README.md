<div align="center">
  <img src="logo-colored.svg" width="50%" height="auto">
  <br><br>

[![CI Status](https://github.com/calebzulawski/hippo/workflows/Continuous%20Integration/badge.svg)](https://github.com/calebzulawski/hippo)
[![Documentation Status](https://github.com/calebzulawski/hippo/workflows/Documentation/badge.svg)](https://calebzulawski.github.io/hippo)
![GitHub](https://img.shields.io/github/license/calebzulawski/hippo)
[![GitHub release](https://img.shields.io/github/v/release/calebzulawski/hippo?include_prereleases&sort=semver)](https://github.com/calebzulawski/hippo/releases)

</div>

## What is it?
Hippo is short for Hierarchical Information as Pretty-Printed Objects.

It is a header-only library for C++17 that makes it easy to display the contents of nested data structures in an intelligent and legible manner.

To get started, see the [latest documentation of the master branch here](https://calebzulawski.github.io/hippo/).

## Key features
* Out-of-the-box printers for all builtin types and most standard library types
* Printers for user-defined types created via reflection macros (`class`/`struct` and `enum`/`enum class`)
* All types, even polymorphic types, can be printed without modifying the type
* Configurable indentation level and output text column count
  
## A simple example
Custom class types can be made printable with the reflection helper macros `HIPPO_CLASS_BEGIN`, `HIPPO_MEMBER`, and `HIPPO_CLASS_END`.

```c++
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
```

When run, this program produces:
```
Expanded:
Bar {
  foos: std::map [
    (
      key: 1,
      value: Foo {
        a: 0,
        b: 0
      }
    ),
    (
      key: 2,
      value: Foo {
        a: 1,
        b: 2
      }
    )
  ]
}
Condensed:
Bar {
  foos: std::map [
    ( key: 1, value: Foo { a: 0, b: 0 } ),
    ( key: 2, value: Foo { a: 1, b: 2 } )
  ]
}
```

## Logo
"[hippo](https://thenounproject.com/edharrison89/collection/kingdom-animalia-icons/?i=198549)" by [Ed Harrison](http://edharrisondesign.com/) licensed under [CC BY 3.0](https://creativecommons.org/licenses/by/3.0/)
