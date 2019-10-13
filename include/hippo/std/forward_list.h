#ifndef HIPPO_STD_FORWARD_LIST_H_
#define HIPPO_STD_FORWARD_LIST_H_

#include "../detail/containers.h"
#include <forward_list>

namespace hippo {

//!\cond
template <typename... T>
struct printer<std::forward_list<T...>>
    : detail::arraylike_base<std::forward_list<T...>,
                             printer<std::forward_list<T...>>> {
  constexpr static const char *prefix = "std::forward_list";
};
//!\endcond

} // namespace hippo

#endif // HIPPO_STD_FORWARD_LIST_H_
