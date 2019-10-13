#include "hippo/std/unordered_map.h"
#include "catch.hpp"
#include "hippo/hippo.h"
#include <unordered_map>

TEST_CASE("unordered_map") {
  hippo::configuration config;
  config.indent = 2;
  std::unordered_map<int, float> val{{1, 0.5}};
  SECTION("empty") {
    val.clear();
    std::vector<std::string> expected_string{"std::unordered_map [empty]"};
    REQUIRE(hippo::print(val, config) == expected_string);
  }
  SECTION("expanded") {
    config.width = 0;
    std::vector<std::string> expected_string{
        "std::unordered_map [", "  (", "    key: 1,",
        "    value: 0.5",       "  )", "]"};
    REQUIRE(hippo::print(val, config) == expected_string);
  }
  SECTION("compressed") {
    config.width = 100;
    std::vector<std::string> expected_string{
        "std::unordered_map [ ( key: 1, value: 0.5 ) ]"};
    REQUIRE(hippo::print(val, config) == expected_string);
  }
  SECTION("formatted") {
    config.width = 100;
    hippo::map_format<int, float> fmt;
    fmt.first.base = hippo::integer_format::base_type::hex;
    fmt.second.format = hippo::float_format::format_type::scientific;
    fmt.second.precision = 1;
    std::vector<std::string> expected_string{
        "std::unordered_map [ ( key: 0x1, value: 5.0e-01 ) ]"};
    REQUIRE(hippo::print(hippo::formatter(val, fmt), config) ==
            expected_string);
  }
}

TEST_CASE("unordered_multimap") {
  hippo::configuration config;
  config.indent = 2;
  std::unordered_multimap<int, float> val{{1, 0.5}, {1, 0.5}};
  SECTION("empty") {
    val.clear();
    std::vector<std::string> expected_string{"std::unordered_multimap [empty]"};
    REQUIRE(hippo::print(val, config) == expected_string);
  }
  SECTION("expanded") {
    config.width = 0;
    std::vector<std::string> expected_string{"std::unordered_multimap [",
                                             "  (",
                                             "    key: 1,",
                                             "    value: 0.5",
                                             "  ),",
                                             "  (",
                                             "    key: 1,",
                                             "    value: 0.5",
                                             "  )",
                                             "]"};
    REQUIRE(hippo::print(val, config) == expected_string);
  }
  SECTION("compressed") {
    config.width = 100;
    std::vector<std::string> expected_string{
        "std::unordered_multimap [ ( key: 1, value: 0.5 ), ( key: 1, value: "
        "0.5 ) ]"};
    REQUIRE(hippo::print(val, config) == expected_string);
  }
  SECTION("formatted") {
    config.width = 100;
    hippo::map_format<int, float> fmt;
    fmt.first.base = hippo::integer_format::base_type::hex;
    fmt.second.format = hippo::float_format::format_type::scientific;
    fmt.second.precision = 1;
    std::vector<std::string> expected_string{
        "std::unordered_multimap [ ( key: 0x1, value: 5.0e-01 ), ( key: 0x1, "
        "value: 5.0e-01 ) ]"};
    REQUIRE(hippo::print(hippo::formatter(val, fmt), config) ==
            expected_string);
  }
}
