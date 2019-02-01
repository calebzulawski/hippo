#ifndef HIPPO_DETAIL_REFLECTION_H_
#define HIPPO_DETAIL_REFLECTION_H_

#include "base.h"
#include "type_name.h"
#include <list>

#define HIPPO_BEGIN(Type)                                                      \
  namespace hippo {                                                            \
  template <> struct printer<Type> {                                           \
    static std::list<::hippo::line> print(const Type &object,                  \
                                          std::uint64_t current_indent) {      \
      std::list<::hippo::line> lines;                                          \
      lines.emplace_back(current_indent,                                       \
                         ::hippo::detail::type_name<Type>() + " {");

#define HIPPO_END()                                                            \
  lines.emplace_back(current_indent, "}");                                     \
  return lines;                                                                \
  }                                                                            \
  }                                                                            \
  ;                                                                            \
  }

#define HIPPO_MEMBER_EXPR(Name, Expression)                                    \
  {                                                                            \
    using Type = decltype(Expression);                                         \
    auto sublines =                                                            \
        ::hippo::printer<Type>::print((Expression), current_indent + 1);       \
    lines.emplace_back(current_indent + 1,                                     \
                       #Name ": " + sublines.front().string);                  \
    sublines.pop_front();                                                      \
    lines.splice(lines.end(), sublines);                                       \
  }

#define HIPPO_MEMBER(Name) HIPPO_MEMBER_EXPR(Name, object.Name)

#endif // HIPPO_DETAIL_REFLECTION_H_
