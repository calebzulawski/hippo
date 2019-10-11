#include "hippo/std/atomic.h"
#include "catch.hpp"

TEST_CASE("atomic") {
  hippo::configuration config;
  config.indent = 2;
  std::atomic<int> a{5};
  SECTION("expanded") {
    config.width = 0;
    std::vector<std::string> expected{"std::atomic containing [", "  5", "]"};
    REQUIRE(hippo::print(a, config) == expected);
  }
  SECTION("condensed") {
    config.width = 100;
    std::vector<std::string> expected{"std::atomic containing [ 5 ]"};
    REQUIRE(hippo::print(a, config) == expected);
  }
  SECTION("formatted") {
    config.width = 100;
    std::vector<std::string> expected{"std::atomic containing [ 0x5 ]"};
    hippo::integer_format format{hippo::integer_format::base_type::hex};
    REQUIRE(hippo::print(hippo::formatter(a, format), config) == expected);
  }
}
