#include "catch.hpp"
#include "hippo/hippo.h"

TEST_CASE("pointers") {
  hippo::configuration config;
  config.indent = 2;
  hippo::integer_format fmt;
  fmt.base = hippo::integer_format::base_type::hex;
  SECTION("nullptr") {
    int *ptr = nullptr;
    SECTION("expanded") {
      config.width = 0;
      std::vector<std::string> expected_string{{"pointer [nullptr]"}};
      REQUIRE(hippo::print(hippo::formatter(ptr, fmt), config) ==
              expected_string);
      REQUIRE(hippo::print(hippo::formatter(const_cast<const int *>(ptr), fmt),
                           config) == expected_string);
    }
    SECTION("condensed") {
      config.width = 100;
      std::vector<std::string> expected_string{{"pointer [nullptr]"}};
      REQUIRE(hippo::print(hippo::formatter(ptr, fmt), config) ==
              expected_string);
      REQUIRE(hippo::print(hippo::formatter(const_cast<const int *>(ptr), fmt),
                           config) == expected_string);
    }
  }
  SECTION("formatted") {
    int value = 0x55;
    int *ptr = &value;
    SECTION("expanded") {
      config.width = 0;
      std::vector<std::string> expected_string{
          {"pointer containing [", "  0x55", "]"}};
      REQUIRE(hippo::print(hippo::formatter(ptr, fmt), config) ==
              expected_string);
      REQUIRE(hippo::print(hippo::formatter(const_cast<const int *>(ptr), fmt),
                           config) == expected_string);
    }
    SECTION("condensed") {
      config.width = 100;
      std::vector<std::string> expected_string{{"pointer containing [ 0x55 ]"}};
      REQUIRE(hippo::print(hippo::formatter(ptr, fmt), config) ==
              expected_string);
      REQUIRE(hippo::print(hippo::formatter(const_cast<const int *>(ptr), fmt),
                           config) == expected_string);
    }
  }
  SECTION("unformatted") {
    int value = 55;
    int *ptr = &value;
    SECTION("expanded") {
      config.width = 0;
      std::vector<std::string> expected_string{
          {"pointer containing [", "  55", "]"}};
      REQUIRE(hippo::print(ptr, config) == expected_string);
      REQUIRE(hippo::print(const_cast<const int *>(ptr), config) ==
              expected_string);
    }
    SECTION("condensed") {
      config.width = 100;
      std::vector<std::string> expected_string{{"pointer containing [ 55 ]"}};
      REQUIRE(hippo::print(ptr, config) == expected_string);
      REQUIRE(hippo::print(const_cast<const int *>(ptr), config) ==
              expected_string);
    }
  }
}
