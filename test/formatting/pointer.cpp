#include "hippo/formatting/pointer.h"
#include "catch.hpp"
#include "hippo/hippo.h"

struct foo {
  int bar = 5;

  virtual ~foo() = default;
};

struct subfoo : foo {};

struct subsubfoo : subfoo {};

struct nonefoo : foo {};

HIPPO_CLASS_BEGIN(foo)
HIPPO_MEMBER(bar)
HIPPO_CLASS_END()

HIPPO_CLASS_BEGIN(subfoo)
HIPPO_BASE(foo)
HIPPO_CLASS_END()

HIPPO_CLASS_BEGIN(subsubfoo)
HIPPO_BASE(subfoo)
HIPPO_CLASS_END()

HIPPO_CLASS_BEGIN(nonefoo)
HIPPO_BASE(foo)
HIPPO_CLASS_END()

TEST_CASE("format-pointer") {
  hippo::configuration config;
  config.indent = 2;
  config.width = 100;
  subsubfoo sff;
  foo *f = &sff;
  SECTION("standard") {
    hippo::pointer_format<foo> fmt = hippo::standard_pointer_format<foo>();
    hippo::line got =
        std::get<hippo::line>(hippo::apply_format(f, 1, config, fmt));
    REQUIRE(got.indent == 1);
    REQUIRE(got.string == "foo { bar: 5 }");
  }
  SECTION("address") {
    hippo::pointer_format<foo> fmt = hippo::address_format();
    std::ostringstream ss;
    ss << f;
    hippo::line got =
        std::get<hippo::line>(hippo::apply_format(f, 1, config, fmt));
    REQUIRE(got.indent == 1);
    REQUIRE(got.string == ss.str());
  }
  SECTION("dynamic") {
    // base printer
    hippo::pointer_format<foo> fmt = hippo::dynamic_type_format<foo>();
    auto &dfmt = std::get<hippo::dynamic_type_format<foo>>(fmt);
    {
      hippo::line got =
          std::get<hippo::line>(hippo::apply_format(f, 1, config, fmt));
      REQUIRE(got.indent == 1);
      REQUIRE(got.string == "foo { bar: 5 }");
    }

    // no matching derived type
    dfmt.printers.push_back(
        std::make_shared<hippo::derived_type_printer<foo, nonefoo>>());
    {
      hippo::line got =
          std::get<hippo::line>(hippo::apply_format(f, 1, config, fmt));
      REQUIRE(got.indent == 1);
      REQUIRE(got.string == "foo { bar: 5 }");
    }

    // matching derived type
    dfmt.printers.push_back(
        std::make_shared<hippo::derived_type_printer<foo, subsubfoo>>());
    {
      hippo::line got =
          std::get<hippo::line>(hippo::apply_format(f, 1, config, fmt));
      REQUIRE(got.indent == 1);
      REQUIRE(got.string ==
              "subsubfoo { Base subfoo { Base foo { bar: 5 } } }");
    }

    // matching derived type, with earlier type taking priority
    dfmt.printers.insert(
        dfmt.printers.begin(),
        std::make_shared<hippo::derived_type_printer<foo, subfoo>>());
    {
      hippo::line got =
          std::get<hippo::line>(hippo::apply_format(f, 1, config, fmt));
      REQUIRE(got.indent == 1);
      REQUIRE(got.string == "subfoo { Base foo { bar: 5 } }");
    }
  }
}
