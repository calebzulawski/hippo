#include "catch.hpp"
#include "hippo/hippo.h"

struct Foo {};

HIPPO_CLASS_BEGIN(Foo)
HIPPO_CLASS_END()

TEST_CASE("const volatile type") {
  hippo::configuration config;
  config.indent = 2;
  Foo foo;
  std::string expected("Foo { }");
  REQUIRE(
      std::get<hippo::line>(hippo::printer<const Foo>::print(foo, 0, config))
          .string == expected);
  REQUIRE(
      std::get<hippo::line>(hippo::printer<volatile Foo>::print(foo, 0, config))
          .string == expected);
  REQUIRE(std::get<hippo::line>(
              hippo::printer<const volatile Foo>::print(foo, 0, config))
              .string == expected);
}
