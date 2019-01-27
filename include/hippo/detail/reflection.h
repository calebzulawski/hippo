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
    static std::vector<::hippo::line> print(const Type &object,                \
                                            std::uint64_t current_indent) {    \
      std::vector<::hippo::line> lines;

#define HIPPO_END()                                                            \
  return lines;                                                                \
  }                                                                            \
  }                                                                            \
  ;                                                                            \
  }

#define HIPPO_MEMBER_EXPR(Name, Expression)                                    \
  {                                                                            \
    using Type = decltype(Expression);                                         \
    auto sublines = ::hippo::detail::print_with_prefix(                        \
        #Name ":", (Expression), current_indent);                              \
    lines.insert(lines.end(), sublines.begin(), sublines.end());               \
  }

#define HIPPO_MEMBER(Name) HIPPO_MEMBER_EXPR(Name, object.Name)

#endif // HIPPO_DETAIL_REFLECTION_H_
