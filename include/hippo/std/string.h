#ifndef HIPPO_STD_STRING_H_
#define HIPPO_STD_STRING_H_

#include "../detail/strings.h"
#include "../hippo.h"
#include <string>

namespace hippo {

//!\cond
template <>
struct printer<std::string>
    : hippo::detail::stringlike<std::string, printer<std::string>> {
  using format_type = ::hippo::no_format;
  constexpr static const char *prefix = "std::string";
};
//!\endcond

} // namespace hippo

#endif // HIPPO_STD_STRING_H_
