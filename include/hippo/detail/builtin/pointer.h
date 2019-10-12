#ifndef HIPPO_DETAIL_BUILTIN_POINTER_H_
#define HIPPO_DETAIL_BUILTIN_POINTER_H_

#include "../../formatting/pointer.h"
#include "../base.h"
#include <type_traits>

namespace hippo {

//!\cond
template <typename T> struct printer<T *> {
  using value_type = std::remove_const_t<T>;
  using format_type = ::hippo::pointer_format<value_type>;
  static ::hippo::object print(const value_type *o,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type &format = format_type()) {
    if (o) {
      std::list<::hippo::object> objects;
      objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                           "pointer containing [");
      objects.push_back(
          ::hippo::apply_format(o, current_indent + 1, config, format));
      objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                           "]");
      return ::hippo::condense(objects, config);
    } else {
      return ::hippo::object{std::in_place_type<::hippo::line>, current_indent,
                             "pointer [nullptr]"};
    }
  }
};
//!\endcond

} // namespace hippo

#endif // HIPPO_DETAIL_BUILTIN_POINTER_H_
