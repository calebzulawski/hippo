#ifndef HIPPO_DETAIL_NUMBERS_H_
#define HIPPO_DETAIL_NUMBERS_H_

#include "base.h"
#include <type_traits>

namespace hippo {

template <typename T>
struct printer<T, std::enable_if_t<
                      std::is_arithmetic_v<T> && !std::is_same_v<T, bool>, T>> {
  static std::list<::hippo::line> print(const T &t,
                                        std::uint64_t current_indent,
                                        const ::hippo::configuration &) {
    return {{current_indent, std::to_string(t)}};
  }
};

template <> struct printer<bool> {
  static std::list<::hippo::line> print(const bool &b,
                                        std::uint64_t current_indent,
                                        const ::hippo::configuration &) {
    return {{current_indent, b ? "true" : "false"}};
  }
};

} // namespace hippo

#endif // HIPPO_DETAIL_NUMBERS_H_
