#include "catch.hpp"
#include "hippo/hippo.h"

using namespace std::literals::string_literals;

namespace test {
enum class EnumClass {
  Value1,
  Value2,
  Missing,
};

namespace scope {
enum EnumType {
  Value1,
  Value2,
  Missing,
};
}
} // namespace test

enum UnscopedEnumType {
  Value1,
  Value2,
  Missing,
};

HIPPO_ENUM_BEGIN(test::EnumClass)
HIPPO_ENUM_VALUE(test::EnumClass::Value1)
HIPPO_ENUM_VALUE(test::EnumClass::Value2)
HIPPO_ENUM_END()

HIPPO_ENUM_BEGIN(test::scope::EnumType)
HIPPO_ENUM_VALUE(test::scope::Value1)
HIPPO_ENUM_VALUE(test::scope::Value2)
HIPPO_ENUM_END()

HIPPO_ENUM_BEGIN(UnscopedEnumType)
HIPPO_ENUM_VALUE(Value1)
HIPPO_ENUM_VALUE(Value2)
HIPPO_ENUM_END()

TEST_CASE("enum class") {
  hippo::configuration config;
  auto [enum_value, expected] =
      GENERATE(std::pair{test::EnumClass::Value1,
                         std::vector{"enum test::EnumClass [Value1]"s}},
               std::pair{test::EnumClass::Value2,
                         std::vector{"enum test::EnumClass [Value2]"s}},
               std::pair{test::EnumClass::Missing,
                         std::vector{"enum test::EnumClass [unknown value]"s}});
  REQUIRE(hippo::print(enum_value, config) == expected);
}

TEST_CASE("enum in namespace") {
  hippo::configuration config;
  auto [enum_value, expected] = GENERATE(
      std::pair{test::scope::Value1,
                std::vector{"enum test::scope::EnumType [Value1]"s}},
      std::pair{test::scope::Value2,
                std::vector{"enum test::scope::EnumType [Value2]"s}},
      std::pair{test::scope::Missing,
                std::vector{"enum test::scope::EnumType [unknown value]"s}});
  REQUIRE(hippo::print(enum_value, config) == expected);
}

TEST_CASE("enum not in namespace") {
  hippo::configuration config;
  auto [enum_value, expected] = GENERATE(
      std::pair{Value1, std::vector{"enum UnscopedEnumType [Value1]"s}},
      std::pair{Value2, std::vector{"enum UnscopedEnumType [Value2]"s}},
      std::pair{Missing,
                std::vector{"enum UnscopedEnumType [unknown value]"s}});
  REQUIRE(hippo::print(enum_value, config) == expected);
}

namespace foo {
struct bar {
  int member1 = 1;
  std::string member2 = "2";
  int member3 = 3;
  const int member4 = 4;
};
} // namespace foo

HIPPO_CLASS_BEGIN(foo::bar)
HIPPO_MEMBER(member1)
HIPPO_MEMBER(member2)
HIPPO_MEMBER_EXPR(lvalue, object.member3)
HIPPO_MEMBER_EXPR(clvalue, object.member4)
HIPPO_MEMBER_EXPR(rvalue, std::string("5"));
HIPPO_MEMBER_EXPR(lambda, []() { return 6; }())
HIPPO_CLASS_END()

TEST_CASE("struct") {
  hippo::configuration config;
  foo::bar o;
  SECTION("expanded") {
    config.width = 0;
    REQUIRE(hippo::print(o, config) ==
            std::vector{"foo::bar {"s, "  member1: 1,"s,
                        "  member2: std::string ["s, "    2"s, "  ],"s,
                        "  lvalue: 3,"s, "  clvalue: 4,"s,
                        "  rvalue: std::string ["s, "    5"s, "  ],"s,
                        "  lambda: 6"s, "}"s});
  }
  SECTION("condensed") {
    config.width = 200;
    REQUIRE(
        hippo::print(o, config) ==
        std::vector{
            "foo::bar { member1: 1, member2: std::string [ 2 ], lvalue: 3, clvalue: 4, rvalue: std::string [ 5 ], lambda: 6 }"s});
  }
}
