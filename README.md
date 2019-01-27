# Hippo (Hierarchical Information Pretty-Printer Objects)

Support for:
* Custom type printers via reflection macros
* Builtin types
  * Arithmetic types
  * C-style arrays
* Containers:
  * `std::array`
  * `std::vector`
  * `std::list`, `std::forward_list`
  * `std::deque`
  * `std::set`, `std::multiset`, `std::unordered_set`, `std::unordered_multiset`
  
## Defining a custom type printer
Custom types can be made printable with the reflection helper macros `HIPPO_BEGIN`, `HIPPO_MEMBER`, `HIPPO_MEMBER_EXPR`, and `HIPPO_END`.
```c++
#include "hippo/hippo.h"
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
HIPPO_BEGIN(A)
HIPPO_MEMBER(a1)
HIPPO_MEMBER_EXPR(a2, object.a2 < 0 ? -object.a2 : object.a2) // custom expressions are allowed
HIPPO_END()

// Make B printable
HIPPO_BEGIN(B)
HIPPO_MEMBER(b1) // std::vector<A> is automatically printable because A is
HIPPO_MEMBER(b2)
HIPPO_END()
```
