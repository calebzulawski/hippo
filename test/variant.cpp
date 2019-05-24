#include "catch.hpp"
#include "hippo/hippo.h"

struct immovable {
  immovable() {}
  immovable(const immovable &) { throw 0; }
  immovable(immovable &&) { throw 0; }
  immovable &operator=(immovable &&) { throw 0; }
};

HIPPO_CLASS_BEGIN(immovable);
HIPPO_CLASS_END();

TEST_CASE("variant") {
  hippo::configuration config;
  config.indent = 2;
  std::variant<int, std::string, immovable> v;
  SECTION("int") {
    v = 123;
    SECTION("expanded") {
      config.width = 0;
      std::vector<std::string> expected_string{
          {"std::variant containing [", "  123", "]"}};
      REQUIRE(hippo::print(v, config) == expected_string);
    }
    SECTION("condensed") {
      config.width = 100;
      std::vector<std::string> expected_string{
          {"std::variant containing [ 123 ]"}};
      REQUIRE(hippo::print(v, config) == expected_string);
    }
  }
  SECTION("string") {
    v = std::string("hello");
    SECTION("expanded") {
      config.width = 0;
      std::vector<std::string> expected_string{{"std::variant containing [",
                                                "  std::string [", "    hello",
                                                "  ]", "]"}};
      REQUIRE(hippo::print(v, config) == expected_string);
    }
    SECTION("condensed") {
      config.width = 100;
      std::vector<std::string> expected_string{
          {"std::variant containing [ std::string [ hello ] ]"}};
      REQUIRE(hippo::print(v, config) == expected_string);
    }
  }
  SECTION("valueless") {
    try {
      v = immovable();
    } catch (...) {
    }
    std::vector<std::string> expected_string{{"std::variant [valueless]"}};
    REQUIRE(hippo::print(v, config) == expected_string);
  }
}
