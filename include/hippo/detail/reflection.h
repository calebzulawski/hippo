#ifndef HIPPO_DETAIL_REFLECTION_H_
#define HIPPO_DETAIL_REFLECTION_H_

#include "base.h"

#define HIPPO_BEGIN(Type)                                                      \
  namespace hippo {                                                            \
  template <> struct printer<Type> {                                           \
    static std::string prefix() {                                              \
      return ::hippo::detail::type_name<Type>().append(" {");                  \
    }                                                                          \
    static std::string suffix() { return "}"; }                                \
    static std::vector<std::string> print(const Type &object,                  \
                                          std::uint64_t indent,                \
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
    ::hippo::detail::print_with_prefix(#Name ":", (Expression), lines, indent, \
                                       current_indent);                        \
  }

#define HIPPO_MEMBER(Name) HIPPO_MEMBER_EXPR(Name, object.Name)

#endif // HIPPO_DETAIL_REFLECTION_H_
