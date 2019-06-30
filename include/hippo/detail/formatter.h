#ifndef HIPPO_DETAIL_FORMATTER_H_
#define HIPPO_DETAIL_FORMATTER_H_

#include "base.h"
#include <type_traits>
#include <utility>

namespace hippo {

struct no_format {};

template <typename T> struct formatter {
  using value_type = T;
  using format_type = typename ::hippo::printer<T>::format_type;

  formatter() = delete;
  formatter(const formatter &) = delete;
  formatter(formatter &&) = delete;

  formatter(const value_type &value, const format_type &format)
      : value(value), format(format) {}

  friend class ::hippo::printer<formatter>;

private:
  const value_type &value;
  const format_type &format;
};

template <typename T>
formatter(const T &, const typename ::hippo::printer<T>::format_type &)
    ->formatter<T>;

template <typename T> struct printer<formatter<T>> {
  static ::hippo::object print(const formatter<T> &o,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &config) {
    return ::hippo::printer<T>::print(o.value, current_indent, config,
                                      o.format);
  }
};

} // namespace hippo

#endif // HIPPO_DETAIL_FORMATTER_H_
