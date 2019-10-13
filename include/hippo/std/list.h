#ifndef HIPPO_STD_LIST_H_
#define HIPPO_STD_LIST_H_

#include "../detail/containers.h"
#include <list>

namespace hippo {

//!\cond
template <typename... T>
struct printer<std::list<T...>>
    : detail::arraylike_base<std::list<T...>, printer<std::list<T...>>> {
  constexpr static const char *prefix = "std::list";
};
//!\endcond

} // namespace hippo

#endif // HIPPO_STD_LIST_H_
