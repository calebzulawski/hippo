#ifndef HIPPO_STD_OPTIONAL_H_
#define HIPPO_STD_OPTIONAL_H_

#include "../hippo.h"
#include <list>
#include <optional>

namespace hippo {

template <typename T> struct printer<std::optional<T>> {
  static ::hippo::object print(const std::optional<T> &o,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &config) {
    if (o) {
      std::list<::hippo::object> objects;
      objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                           "std::optional containing [");
      objects.push_back(
          ::hippo::printer<T>::print(*o, current_indent + 1, config));
      objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                           "]");
      return ::hippo::condense(objects, config);
    } else {
      return ::hippo::object{std::in_place_type<::hippo::line>, current_indent,
                             "std::optional [empty]"};
    }
  }
};

} // namespace hippo

#endif // HIPPO_STD_OPTIONAL_H_
