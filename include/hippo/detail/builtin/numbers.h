#ifndef HIPPO_DETAIL_BUILTIN_NUMBERS_H_
#define HIPPO_DETAIL_BUILTIN_NUMBERS_H_

#include "../../formatting/float.h"
#include "../../formatting/integer.h"
#include "../base.h"
#include <type_traits>

namespace hippo {

template <typename T>
struct printer<
    T, std::enable_if_t<std::is_integral_v<T> && !std::is_same_v<T, bool>, T>> {
  using format_type = ::hippo::integer_format;
  static ::hippo::object print(const T &t, std::uint64_t current_indent,
                               const ::hippo::configuration &,
                               const format_type &format = format_type()) {
    return ::hippo::object{std::in_place_type<::hippo::line>, current_indent,
                           ::hippo::detail::apply_format(t, format)};
  }
};

template <typename T>
struct printer<T, std::enable_if_t<std::is_floating_point_v<T>, T>> {
  using format_type = ::hippo::float_format;
  static ::hippo::object print(const T &t, std::uint64_t current_indent,
                               const ::hippo::configuration &,
                               const format_type &format = format_type()) {
    return ::hippo::object{std::in_place_type<::hippo::line>, current_indent,
                           ::hippo::detail::apply_format(t, format)};
  }
};

template <> struct printer<bool> {
  static ::hippo::object print(const bool &b, std::uint64_t current_indent,
                               const ::hippo::configuration &) {
    return ::hippo::object{std::in_place_type<::hippo::line>, current_indent,
                           b ? "true" : "false"};
  }
};

} // namespace hippo

#endif // HIPPO_DETAIL_NUMBERS_H_
