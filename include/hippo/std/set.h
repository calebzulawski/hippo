#ifndef HIPPO_STD_SET_H_
#define HIPPO_STD_SET_H_

#include "../detail/containers.h"
#include <set>

namespace hippo {

template <typename... T>
struct printer<std::set<T...>>
    : detail::arraylike_base<std::set<T...>, printer<std::set<T...>>> {
  constexpr static const char *prefix = "std::set [";
};

template <typename... T>
struct printer<std::multiset<T...>>
    : detail::arraylike_base<std::multiset<T...>,
                             printer<std::multiset<T...>>> {
  constexpr static const char *prefix = "std::multiset [";
};

} // namespace hippo

#endif // HIPPO_STD_SET_H_
