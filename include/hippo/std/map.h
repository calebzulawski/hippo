#ifndef HIPPO_STD_MAP_H_
#define HIPPO_STD_MAP_H_

#include "../detail/containers.h"
#include <map>

namespace hippo {

//!\cond
template <typename... T>
struct printer<std::map<T...>>
    : detail::maplike_base<std::map<T...>, printer<std::map<T...>>> {
  constexpr static const char *prefix = "std::map [";
};

template <typename... T>
struct printer<std::multimap<T...>>
    : detail::maplike_base<std::multimap<T...>, printer<std::multimap<T...>>> {
  constexpr static const char *prefix = "std::multimap [";
};
//!\endcond

} // namespace hippo

#endif // HIPPO_STD_MAP_H_
