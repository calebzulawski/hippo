#include "pointer.h"
#include "catch.hpp"
#include "hippo/hippo.h"

TEST_CASE("pointers") {
  hippo::configuration config;
  config.indent = 2;
  SECTION("nullptr") {
    int *ptr = nullptr;
    const int *const_ptr = nullptr;
    NULLPTR_SECTIONS("pointer");
  }
  SECTION("formatted") {
    int value = 0x55;
    int *ptr = &value;
    const int *const_ptr = ptr;
    hippo::pointer_format<int> fmt = hippo::standard_pointer_format<int>();
    std::get<hippo::standard_pointer_format<int>>(fmt).format.base =
        hippo::integer_format::base_type::hex;
    FORMATTED_SECTIONS("pointer", "0x55");
  }
  SECTION("unformatted") {
    int value = 55;
    int *ptr = &value;
    const int *const_ptr = ptr;
    VALUE_SECTIONS("pointer", "55");
  }
}
