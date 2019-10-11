# Printing user-defined types with reflection

## The basics
Hippo provides utilities for printing user-defined types. Consider the following types:
```c++
struct Foo {
    int a;
    float b;
};

struct Bar {
    std::vector<Foo> foos;
};
```

To print these types, we must reflect the members:
```c++
#include "hippo/hippo.h"       // provides support for builtin types, including structs 
#include "hippo/std/vector.h"  // provides support for std::vector

HIPPO_CLASS_BEGIN(Foo)
  HIPPO_MEMBER(a)
  HIPPO_MEMBER(b)
HIPPO_CLASS_END()

HIPPO_CLASS_BEGIN(Bar)
  HIPPO_MEMBER(foos)
HIPPO_CLASS_END()
```

The printers for `int`, `float`, and `std::vector` are all provided by Hippo.
Once we've provided the printer for `Foo`, we are able to use it to print `Bar`.
A printed instance of `Bar` might look something like this:
```
Bar {
  foos: std::vector [
    Foo { a: 1, b: 0.5 },
    Foo { a: 2, b: -3.1 }
  ]
}
```

## Enums
Similarly, enums can be reflected:
```c++
enum Foo {
    Bar,
    Baz
};

HIPPO_ENUM_BEGIN(Foo)
  HIPPO_ENUM_VALUE(Bar)
  HIPPO_ENUM_VALUE(Baz)
HIPPO_ENUM_END()
```

## Base classes
Hippo can also reflect base classes:
```c++
struct Foo : Bar {
    /* members */
};

HIPPO_CLASS_BEGIN(Foo)
  HIPPO_BASE(Bar)
  /* members */
HIPPO_CLASS_END()
```

## Custom member access expressions
In some cases, it's useful to use another expression to access a member.
This is accomplished by using the `HIPPO_MEMBER_EXPR` macro, which allows a custom expression to be provided, operating on the input `object`:
```c++
class Foo {
    int bar;
public:
    Foo(int bar) : bar(bar) {}
    int get_bar() const { return bar; }
};

HIPPO_CLASS_BEGIN(Foo)
  HIPPO_MEMBER_EXPR(bar, object.get_bar())
HIPPO_CLASS_END()
```
    
