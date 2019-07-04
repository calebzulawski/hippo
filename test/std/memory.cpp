#include "hippo/std/memory.h"
#include "catch.hpp"
#include "pointer.h"
#include <memory>

void no_delete(const int *) {}

TEST_CASE("unique_ptr") {
  hippo::configuration config;
  config.indent = 2;
  SECTION("nullptr") {
    std::unique_ptr<int, void (*)(const int *)> ptr(nullptr, &no_delete);
    std::unique_ptr<const int, void (*)(const int *)> const_ptr(nullptr,
                                                                &no_delete);
    NULLPTR_SECTIONS("std::unique_ptr");
  }
  SECTION("formatted") {
    auto ptr = std::make_unique<int>(0x55);
    auto const_ptr = std::make_unique<const int>(0x55);
    hippo::pointer_format<int> fmt = hippo::standard_pointer_format<int>();
    std::get<hippo::standard_pointer_format<int>>(fmt).format.base =
        hippo::integer_format::base_type::hex;
    FORMATTED_SECTIONS("std::unique_ptr", "0x55");
  }
  SECTION("unformatted") {
    auto ptr = std::make_unique<int>(55);
    auto const_ptr = std::make_unique<const int>(55);
    VALUE_SECTIONS("std::unique_ptr", "55");
  }
}

TEST_CASE("shared_ptr") {
  hippo::configuration config;
  config.indent = 2;
  SECTION("nullptr") {
    std::shared_ptr<int> ptr;
    std::shared_ptr<const int> const_ptr;
    NULLPTR_SECTIONS("std::shared_ptr");
  }
  SECTION("formatted") {
    auto ptr = std::make_shared<int>(0x55);
    auto const_ptr = std::const_pointer_cast<const int>(ptr);
    hippo::pointer_format<int> fmt = hippo::standard_pointer_format<int>();
    std::get<hippo::standard_pointer_format<int>>(fmt).format.base =
        hippo::integer_format::base_type::hex;
    FORMATTED_SECTIONS("std::shared_ptr", "0x55");
  }
  SECTION("unformatted") {
    auto ptr = std::make_shared<int>(55);
    auto const_ptr = std::const_pointer_cast<const int>(ptr);
    VALUE_SECTIONS("std::shared_ptr", "55");
  }
}

TEST_CASE("weak_ptr") {
  hippo::configuration config;
  config.indent = 2;
  SECTION("nullptr") {
    std::weak_ptr<int> ptr;
    std::weak_ptr<const int> const_ptr;
    NULLPTR_SECTIONS("std::weak_ptr");
  }
  SECTION("formatted") {
    auto shared_ptr = std::make_shared<int>(0x55);
    std::weak_ptr<int> ptr = shared_ptr;
    std::weak_ptr<const int> const_ptr = shared_ptr;
    hippo::pointer_format<int> fmt = hippo::standard_pointer_format<int>();
    std::get<hippo::standard_pointer_format<int>>(fmt).format.base =
        hippo::integer_format::base_type::hex;
    FORMATTED_SECTIONS("std::weak_ptr", "0x55");
  }
  SECTION("unformatted") {
    auto shared_ptr = std::make_shared<int>(55);
    std::weak_ptr<int> ptr = shared_ptr;
    std::weak_ptr<const int> const_ptr = shared_ptr;
    VALUE_SECTIONS("std::weak_ptr", "55");
  }
}
