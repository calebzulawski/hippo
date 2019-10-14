#include "catch.hpp"
#include "hippo/hippo.h"

TEMPLATE_TEST_CASE("integer", "[builtin]", std::uint8_t, std::uint16_t,
                   std::uint32_t, std::uint64_t, std::int8_t, std::int16_t,
                   std::int32_t, std::int64_t) {
  TestType value = 2;
  hippo::configuration config;
  SECTION("decimal") {
    std::vector<std::string> expected{"2"};
    REQUIRE(hippo::print(value, config) == expected);
  }
  SECTION("octal") {
    hippo::integer_format fmt;
    fmt.base = hippo::integer_format::base_type::oct;
    std::vector<std::string> expected{"02"};
    REQUIRE(hippo::print(hippo::formatter(value, fmt), config) == expected);
  }
  SECTION("hexadecimal") {
    hippo::integer_format fmt;
    fmt.base = hippo::integer_format::base_type::hex;
    std::vector<std::string> expected{"0x2"};
    REQUIRE(hippo::print(hippo::formatter(value, fmt), config) == expected);
  }
}

TEMPLATE_TEST_CASE("float", "[builtin]", float, double, long double) {
  TestType value = 0.5;
  hippo::configuration config;
  SECTION("default") {
    std::vector<std::string> expected{"0.5"};
    REQUIRE(hippo::print(value, config) == expected);
  }
  SECTION("scientific") {
    hippo::float_format fmt;
    fmt.notation = hippo::float_format::notation_type::scientific;
    fmt.precision = 2;
    std::vector<std::string> expected{"5.00e-01"};
    REQUIRE(hippo::print(hippo::formatter(value, fmt), config) == expected);
  }
  SECTION("fixed") {
    hippo::float_format fmt;
    fmt.notation = hippo::float_format::notation_type::fixed;
    fmt.precision = 2;
    std::vector<std::string> expected{"0.50"};
    REQUIRE(hippo::print(hippo::formatter(value, fmt), config) == expected);
  }
}

TEST_CASE("bool") {
  hippo::configuration config;
  std::vector<std::string> expected_false{"false"};
  std::vector<std::string> expected_true{"true"};
  REQUIRE(hippo::print(false, config) == expected_false);
  REQUIRE(hippo::print(true, config) == expected_true);
}
