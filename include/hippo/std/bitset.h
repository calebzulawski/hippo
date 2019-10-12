#ifndef HIPPO_STD_BITSET_H_
#define HIPPO_STD_BITSET_H_

#include "../hippo.h"
#include <bitset>
#include <list>

namespace hippo {

//!\cond
template <std::size_t N> struct printer<std::bitset<N>> {
  using format_type = ::hippo::no_format;
  static ::hippo::object print(const std::bitset<N> &o,
                               std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type & = format_type()) {
    std::list<::hippo::object> objects;
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         "std::bitset containing [");
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent + 1,
                         o.to_string());
    objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,
                         "]");
    return ::hippo::condense(objects, config);
  }
};
//!\endcond

} // namespace hippo

#endif // HIPPO_STD_BITSET_H_
