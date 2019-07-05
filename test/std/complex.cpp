#include "hippo/std/complex.h"
#include "catch.hpp"
#include <complex>
#include <cstdint>

TEST_CASE("complex") {
  hippo::configuration config;
  config.indent = 2;
  SECTION("double") {
    std::complex<double> c(1.2, -34.5);
    SECTION("unformatted") {
      std::vector<std::string> expected_string{"1.2 - 34.5i"};
      REQUIRE(hippo::print(c, config) == expected_string);
    }
    SECTION("formatted") {
      hippo::float_format fmt;
      fmt.format = hippo::float_format::format_type::scientific;
      fmt.precision = 1;
      std::vector<std::string> expected_string{"1.2e+00 - 3.4e+01i"};
      REQUIRE(hippo::print(hippo::formatter(c, fmt), config) ==
              expected_string);
    }
  }
  SECTION("int") {
    std::complex<std::int32_t> c(-5, 10);
    SECTION("unformatted") {
      std::vector<std::string> expected_string{"-5 + 10i"};
      REQUIRE(hippo::print(c, config) == expected_string);
    }
    SECTION("formatted") {
      hippo::integer_format fmt;
      fmt.base = hippo::integer_format::base_type::hex;
      std::vector<std::string> expected_string{"0xfffffffb + 0xai"};
      REQUIRE(hippo::print(hippo::formatter(c, fmt), config) ==
              expected_string);
    }
  }
}
