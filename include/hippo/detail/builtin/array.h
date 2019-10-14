#ifndef HIPPO_DETAIL_BUILTIN_ARRAY_H_
#define HIPPO_DETAIL_BUILTIN_ARRAY_H_

#include "../containers.h"

namespace hippo {

//! Printer specialization for an array `T[N]`
//@headerfile array.h "hippo/hippo.h"
template <typename T, std::size_t N>
struct printer<T[N]> : detail::arraylike_base<T[N], printer<T[N]>> {
  //!@cond
  constexpr static const char *prefix = "native array";
  //!@endcond
};

} // namespace hippo

#endif // HIPPO_DETAIL_BUILTIN_ARRAY_H_
