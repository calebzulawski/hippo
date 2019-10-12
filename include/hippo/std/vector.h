#ifndef HIPPO_STD_VECTOR_H_
#define HIPPO_STD_VECTOR_H_

#include "../detail/containers.h"
#include <vector>

namespace hippo {

//!\cond
template <typename... T>
struct printer<std::vector<T...>>
    : detail::arraylike_base<std::vector<T...>, printer<std::vector<T...>>> {
  constexpr static const char *prefix = "std::vector [";
};
//!\endcond

} // namespace hippo

#endif // HIPPO_STD_VECTOR_H_
