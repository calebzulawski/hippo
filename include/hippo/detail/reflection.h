#ifndef HIPPO_DETAIL_REFLECTION_H_
#define HIPPO_DETAIL_REFLECTION_H_

#include "base.h"

namespace hippo::detail {

template <typename T>
void print_member(const char *name, const T &value,
                  std::vector<std::string> &lines, std::uint64_t indent,
                  std::uint64_t current_indent) {
  std::string header(current_indent, ' ');
  header.append(name);
  if constexpr (::hippo::has_stringifier<T>::value) {
    header.push_back(' ');
    header.append(::hippo::stringifier<T>::stringify(value));
    lines.emplace_back(std::move(header));
  } else {
    if constexpr (::hippo::has_prefix_v<T>) {
      auto prefix = ::hippo::printer<T>::prefix();
      if (prefix.size() > 0)
        header.append(prefix);
    }
    lines.emplace_back(std::move(header));
    auto sublines =
        ::hippo::detail::deduce_print(value, indent, current_indent + indent);
    lines.insert(lines.end(), std::begin(sublines), std::end(sublines));
    if constexpr (::hippo::has_suffix_v<T>) {
      auto suffix = ::hippo::printer<T>::suffix();
      if (suffix.size() > 0) {
        std::string footer(current_indent, ' ');
        footer.append(suffix);
        lines.emplace_back(std::move(footer));
      }
    }
  }
}

} // namespace hippo::detail

#define HIPPO_BEGIN(Type)                                                      \
  namespace hippo {                                                            \
  template <> struct printer<Type> {                                           \
    static std::string prefix() {                                              \
      return ::hippo::detail::type_name<Type>().append(" {");                  \
    }                                                                          \
    static std::string suffix() { return "}"; }                                \
    static std::vector<std::string> print(const Type &t, std::uint64_t indent, \
                                          std::uint64_t current_indent) {      \
      std::vector<std::string> lines;

#define HIPPO_END()                                                            \
  return lines;                                                                \
  }                                                                            \
  }                                                                            \
  ;                                                                            \
  }

#define HIPPO_MEMBER_EXPR(Name, Expression)                                    \
  {                                                                            \
    using Type = decltype(Expression);                                         \
    ::hippo::detail::print_member(#Name ":", (Expression), lines, indent,      \
                                  current_indent);                             \
  }

#define HIPPO_MEMBER(Name) HIPPO_MEMBER_EXPR(Name, t.Name)

#endif // HIPPO_DETAIL_REFLECTION_H_
