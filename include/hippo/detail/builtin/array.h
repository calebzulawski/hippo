#ifndef HIPPO_DETAIL_BUILTIN_ARRAY_H_
#define HIPPO_DETAIL_BUILTIN_ARRAY_H_

#include "../containers.h"

namespace hippo {

template <typename T, std::size_t N>
struct printer<T[N]> : detail::arraylike_base<T[N], printer<T[N]>> {
  constexpr static const char *prefix = "native array [";
};

} // namespace hippo

#endif // HIPPO_DETAIL_BUILTIN_ARRAY_H_
