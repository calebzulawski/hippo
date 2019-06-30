#include "hippo/std/bitset.h"
#include "catch.hpp"

TEST_CASE("bitset") {
  hippo::configuration config;
  config.indent = 2;
  std::bitset<5> bits(22);
  SECTION("expanded") {
    config.width = 0;
    std::vector<std::string> expected_string{
        {"std::bitset containing [", "  10110", "]"}};
    REQUIRE(hippo::print(bits, config) == expected_string);
  }
  SECTION("condensed") {
    config.width = 100;
    std::vector<std::string> expected_string{
        {"std::bitset containing [ 10110 ]"}};
    REQUIRE(hippo::print(bits, config) == expected_string);
  }
}
