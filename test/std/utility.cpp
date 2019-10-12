#include "hippo/std/utility.h"
#include "catch.hpp"
#include <utility>

TEST_CASE("pair") {
  hippo::configuration config;
  config.indent = 2;
  std::pair<int, float> p(5, 0.5);
  SECTION("expanded") {
    config.width = 0;
    std::vector<std::string> expected_string{"std::pair {", "  first: 5,",
                                             "  second: 0.5", "}"};
    REQUIRE(hippo::print(p, config) == expected_string);
  }
  SECTION("compressed") {
    config.width = 100;
    std::vector<std::string> expected_string{
        "std::pair { first: 5, second: 0.5 }"};
    REQUIRE(hippo::print(p, config) == expected_string);
  }
  SECTION("formatted") {
    config.width = 100;
    std::pair<hippo::integer_format, hippo::float_format> fmt;
    fmt.first.base = hippo::integer_format::base_type::hex;
    fmt.second.format = hippo::float_format::format_type::scientific;
    fmt.second.precision = 1;
    std::vector<std::string> expected_string{
        "std::pair { first: 0x5, second: 5.0e-01 }"};
    REQUIRE(hippo::print(hippo::formatter(p, fmt), config) == expected_string);
  }
}
