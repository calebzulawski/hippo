#include "hippo/std/tuple.h"
#include "catch.hpp"
#include <tuple>

TEST_CASE("tuple") {
  hippo::configuration config;
  config.indent = 2;
  std::tuple<int, float> t(5, 0.5);
  SECTION("expanded") {
    config.width = 0;
    std::vector<std::string> expected_string{"std::tuple {", "  0: 5,",
                                             "  1: 0.5", "}"};
    REQUIRE(hippo::print(t, config) == expected_string);
  }
  SECTION("compressed") {
    config.width = 100;
    std::vector<std::string> expected_string{"std::tuple { 0: 5, 1: 0.5 }"};
    REQUIRE(hippo::print(t, config) == expected_string);
  }
  SECTION("formatted") {
    config.width = 100;
    hippo::tuple_format<int, float> fmt;
    std::get<0>(fmt).base = hippo::integer_format::base_type::hex;
    std::get<1>(fmt).format = hippo::float_format::format_type::scientific;
    std::get<1>(fmt).precision = 1;
    std::vector<std::string> expected_string{
        "std::tuple { 0: 0x5, 1: 5.0e-01 }"};
    REQUIRE(hippo::print(hippo::formatter(t, fmt), config) == expected_string);
  }
}
