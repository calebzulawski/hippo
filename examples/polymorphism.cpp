#include "hippo/hippo.h"
#include "hippo/std/memory.h"
#include <iostream>

struct Foo {
  virtual ~Foo() = default;
};

struct Bar : Foo {};
struct Baz : Foo {};

HIPPO_CLASS_BEGIN(Foo)
HIPPO_CLASS_END()

HIPPO_CLASS_BEGIN(Bar)
HIPPO_BASE(Foo)
HIPPO_CLASS_END()

HIPPO_CLASS_BEGIN(Baz)
HIPPO_BASE(Foo)
HIPPO_CLASS_END()

int main() {
  std::shared_ptr<Foo> foo = std::make_shared<Foo>();
  std::shared_ptr<Foo> bar = std::make_shared<Bar>();
  std::shared_ptr<Foo> baz = std::make_shared<Baz>();
  hippo::dynamic_type_format<Foo> dyn_fmt;
  dyn_fmt.printers.push_back(
      std::make_shared<hippo::derived_type_printer<Foo, Bar>>());
  dyn_fmt.printers.push_back(
      std::make_shared<hippo::derived_type_printer<Foo, Baz>>());
  hippo::pointer_format<Foo> fmt = std::move(dyn_fmt);
  hippo::print_to(std::cout, hippo::formatter(foo, fmt),
                  hippo::configuration());
  hippo::print_to(std::cout, hippo::formatter(bar, fmt),
                  hippo::configuration());
  hippo::print_to(std::cout, hippo::formatter(baz, fmt),
                  hippo::configuration());
}
