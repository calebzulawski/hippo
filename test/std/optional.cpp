#include "hippo/std/optional.h"
#include "catch.hpp"
#include <optional>

TEST_CASE("optional") {
  hippo::configuration config;
  config.indent = 2;
  SECTION("empty") {
    std::optional<int> o;
    std::vector<std::string> expected_string{"std::optional [empty]"};
    REQUIRE(hippo::print(o, config) == expected_string);
  }
  SECTION("expanded") {
    config.width = 0;
    std::optional<int> o(1);
    std::vector<std::string> expected_string{"std::optional containing [",
                                             "  1", "]"};
    REQUIRE(hippo::print(o, config) == expected_string);
  }
  SECTION("compressed") {
    config.width = 1000;
    std::optional<int> o(1);
    std::vector<std::string> expected_string{"std::optional containing [ 1 ]"};
    REQUIRE(hippo::print(o, config) == expected_string);
  }
  SECTION("formatted") {
    config.width = 1000;
    std::optional<int> o(1);
    hippo::integer_format fmt;
    fmt.base = hippo::integer_format::base_type::hex;
    std::vector<std::string> expected_string{
        "std::optional containing [ 0x1 ]"};
    REQUIRE(hippo::print(hippo::formatter(o, fmt), config) == expected_string);
  }
}
