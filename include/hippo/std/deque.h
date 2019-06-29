#ifndef HIPPO_STD_DEQUE_H_
#define HIPPO_STD_DEQUE_H_

#include "../detail/containers.h"
#include <deque>

namespace hippo {

template <typename... T>
struct printer<std::deque<T...>>
    : detail::arraylike_base<std::deque<T...>, printer<std::deque<T...>>> {
  constexpr static const char *prefix = "std::deque [";
};

} // namespace hippo

#endif // HIPPO_STD_DEQUE_H_
