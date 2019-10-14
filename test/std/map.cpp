#include "hippo/std/map.h"
#include "catch.hpp"
#include "hippo/hippo.h"
#include <map>

#define MAKE_TEST(Test, Name, Type)                                            \
  TEST_CASE(Test) {                                                            \
    hippo::configuration config;                                               \
    config.indent = 2;                                                         \
    Type val{{1, 0.5}, {2, 1}};                                                \
    SECTION("empty") {                                                         \
      val.clear();                                                             \
      std::vector<std::string> expected_string{Name " [empty]"};               \
      REQUIRE(hippo::print(val, config) == expected_string);                   \
    }                                                                          \
    SECTION("expanded") {                                                      \
      config.width = 0;                                                        \
      std::vector<std::string> expected_string{                                \
          Name " [", "  (", "    key: 1,", "    value: 0.5",                   \
          "  ),",    "  (", "    key: 2,", "    value: 1",                     \
          "  )",     "]"};                                                     \
      REQUIRE(hippo::print(val, config) == expected_string);                   \
    }                                                                          \
    SECTION("compressed") {                                                    \
      config.width = 100;                                                      \
      std::vector<std::string> expected_string{                                \
          Name " [ ( key: 1, value: 0.5 ), ( key: 2, value: 1 ) ]"};           \
      REQUIRE(hippo::print(val, config) == expected_string);                   \
    }                                                                          \
    SECTION("formatted") {                                                     \
      config.width = 100;                                                      \
      hippo::map_format<int, float> fmt;                                       \
      fmt.first.base = hippo::integer_format::base_type::hex;                  \
      fmt.second.notation = hippo::float_format::notation_type::scientific;    \
      fmt.second.precision = 1;                                                \
      std::vector<std::string> expected_string{                                \
          Name " [ ( key: 0x1, value: 5.0e-01 ), ( key: 0x2, value: "          \
               "1.0e+00 ) "                                                    \
               "]"};                                                           \
      REQUIRE(hippo::print(hippo::formatter(val, fmt), config) ==              \
              expected_string);                                                \
    }                                                                          \
  }

using map_type = std::map<int, float>;
using multimap_type = std::multimap<int, float>;

MAKE_TEST("map", "std::map", map_type)
MAKE_TEST("multimap", "std::multimap", multimap_type)

// Keys are const, so make sure this works
enum class MapFoo { Bar };

HIPPO_ENUM_BEGIN(MapFoo)
HIPPO_ENUM_VALUE(MapFoo::Bar)
HIPPO_ENUM_END()

TEST_CASE("map with enum key") {
  std::map<MapFoo, MapFoo> m;
  m[MapFoo::Bar] = MapFoo::Bar;
  hippo::configuration config;
  config.width = 100;
  std::vector<std::string> expected{
      "std::map [ ( key: enum MapFoo [Bar], value: enum MapFoo [Bar] ) ]"};
  REQUIRE(hippo::print(m, config) == expected);
}
