#ifndef HIPPO_STD_UNORDERED_MAP_H_
#define HIPPO_STD_UNORDERED_MAP_H_

#include "../detail/containers.h"
#include <unordered_map>

namespace hippo {

//!\cond
template <typename... T>
struct printer<std::unordered_map<T...>>
    : detail::maplike_base<std::unordered_map<T...>,
                           printer<std::unordered_map<T...>>> {
  constexpr static const char *prefix = "std::unordered_map [";
};

template <typename... T>
struct printer<std::unordered_multimap<T...>>
    : detail::maplike_base<std::unordered_multimap<T...>,
                           printer<std::unordered_multimap<T...>>> {
  constexpr static const char *prefix = "std::unordered_multimap [";
};
//!\endcond

} // namespace hippo

#endif // HIPPO_STD_UNORDERED_MAP_H_
