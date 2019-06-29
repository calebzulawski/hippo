#ifndef HIPPO_STD_VARIANT_H_
#define HIPPO_STD_VARIANT_H_

#include "../hippo.h"
#include <variant>

namespace hippo {

template <typename... T> struct printer<std::variant<T...>> {
  static ::hippo::object print(const std::variant<T...> &o,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &config) {
    if (o.valueless_by_exception())
      return ::hippo::line(current_indent, "std::variant [valueless]");
    std::list<::hippo::object> objects;
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         "std::variant containing [");
    (
        [&] {
          if (std::holds_alternative<T>(o))
            objects.push_back(::hippo::printer<T>::print(
                std::get<T>(o), current_indent + 1, config));
        }(),
        ...);
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         "]");
    return ::hippo::condense(objects, config);
  }
};

} // namespace hippo

#endif // HIPPO_STD_VARIANT_H_
