#ifndef HIPPO_STD_ARRAY_H_
#define HIPPO_STD_ARRAY_H_

#include "../detail/containers.h"
#include <array>

namespace hippo {

//!\cond
template <typename T, std::size_t N>
struct printer<std::array<T, N>>
    : detail::arraylike_base<std::array<T, N>, printer<std::array<T, N>>> {
  constexpr static const char *prefix = "std::array";
};
//!\endcond

} // namespace hippo

#endif // HIPPO_STD_ARRAY_H_
