#ifndef HIPPO_DETAIL_REFLECTION_H_
#define HIPPO_DETAIL_REFLECTION_H_

#include "base.h"
#include "type_name.h"
#include <list>
#include <type_traits>

#define HIPPO_BEGIN(Type)                                                      \
  namespace hippo {                                                            \
  template <> struct printer<Type> {                                           \
    static std::list<::hippo::line>                                            \
    print(const Type &object, std::uint64_t current_indent,                    \
          const ::hippo::configuration &config) {                              \
      std::list<std::list<::hippo::line>> members;                             \
      std::list<::hippo::line> lines;                                          \
      lines.emplace_back(current_indent,                                       \
                         ::hippo::detail::type_name<Type>() + " {");

#define HIPPO_END()                                                            \
  auto size = members.size();                                                  \
  for (auto &member : members) {                                               \
    if (--size != 0)                                                           \
      member.back().string += ',';                                             \
    lines.splice(lines.end(), member);                                         \
  }                                                                            \
  lines.emplace_back(current_indent, "}");                                     \
  return lines;                                                                \
  }                                                                            \
  }                                                                            \
  ;                                                                            \
  }

#define HIPPO_BASE(Type)                                                       \
  {                                                                            \
    static_assert(std::is_base_of_v<Type, std::decay_t<decltype(object)>>);    \
    auto sublines =                                                            \
        ::hippo::printer<Type>::print(object, current_indent + 1, config);     \
    ::hippo::line new_front(current_indent + 1,                                \
                            "Base " + sublines.front().string);                \
    sublines.pop_front();                                                      \
    sublines.push_front(new_front);                                            \
    condense(sublines, config);                                                \
    members.emplace_back(std::move(sublines));                                 \
  }

#define HIPPO_MEMBER_EXPR(Name, Expression)                                    \
  {                                                                            \
    using Type =                                                               \
        std::remove_cv_t<std::remove_reference_t<decltype(Expression)>>;       \
    auto sublines = ::hippo::printer<Type>::print((Expression),                \
                                                  current_indent + 1, config); \
    ::hippo::line new_front(current_indent + 1,                                \
                            #Name ": " + sublines.front().string);             \
    sublines.pop_front();                                                      \
    sublines.push_front(new_front);                                            \
    condense(sublines, config);                                                \
    members.emplace_back(std::move(sublines));                                 \
  }

#define HIPPO_MEMBER(Name) HIPPO_MEMBER_EXPR(Name, object.Name)

#endif // HIPPO_DETAIL_REFLECTION_H_
