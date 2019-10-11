#ifndef HIPPO_STD_ATOMIC_H_
#define HIPPO_STD_ATOMIC_H_

#include "../hippo.h"
#include <atomic>
#include <list>

namespace hippo {

template <typename T> struct printer<std::atomic<T>> {
  using printer_type = ::hippo::printer<T>;
  using format_type = typename printer_type::format_type;
  static ::hippo::object print(const std::atomic<T> &o,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type &format = format_type()) {
    std::list<::hippo::object> objects;
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         "std::atomic containing [");
    objects.push_back(
        printer_type::print(o.load(), current_indent + 1, config, format));
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         "]");
    return ::hippo::condense(objects, config);
  }
};

} // namespace hippo

#endif // HIPPO_STD_ATOMIC_H_
