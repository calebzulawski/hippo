#ifndef HIPPO_DETAIL_BUILTIN_POINTER_H_
#define HIPPO_DETAIL_BUILTIN_POINTER_H_

#include "../base.h"

namespace hippo {

template <typename T> struct printer<T *> {
  using printer_type = ::hippo::printer<T>;
  using format_type = typename printer_type::format_type;
  static ::hippo::object print(const T *o, std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type &format = format_type()) {
    if (o) {
      std::list<::hippo::object> objects;
      objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                           "pointer containing [");
      objects.push_back(
          printer_type::print(*o, current_indent + 1, config, format));
      objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                           "]");
      return ::hippo::condense(objects, config);
    } else {
      return ::hippo::object{std::in_place_type<::hippo::line>, current_indent,
                             "pointer [nullptr]"};
    }
  }
};

} // namespace hippo

#endif // HIPPO_DETAIL_BUILTIN_POINTER_H_
