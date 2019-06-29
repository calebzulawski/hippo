#ifndef HIPPO_STD_UNORDERED_SET_H_
#define HIPPO_STD_UNORDERED_SET_H_

#include "../detail/containers.h"
#include <unordered_set>

namespace hippo {

template <typename... T>
struct printer<std::unordered_set<T...>>
    : detail::arraylike_base<std::unordered_set<T...>,
                             printer<std::unordered_set<T...>>> {
  constexpr static const char *prefix = "std::unordered_set [";
};

template <typename... T>
struct printer<std::unordered_multiset<T...>>
    : detail::arraylike_base<std::unordered_multiset<T...>,
                             printer<std::unordered_multiset<T...>>> {
  constexpr static const char *prefix = "std::unordered_multiset [";
};

} // namespace hippo

#endif // HIPPO_STD_UNORDERED_SET_H_
