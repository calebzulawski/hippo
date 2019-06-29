#ifndef HIPPO_DETAIL_REFLECTION_H_
#define HIPPO_DETAIL_REFLECTION_H_

#include "base.h"
#include "type_name.h"
#include <list>
#include <type_traits>

namespace hippo::detail {
constexpr inline std::string_view remove_enum_namespace(std::string_view sv) {
  if (auto pos = sv.find_last_of(':'); pos != std::string_view::npos)
    sv.remove_prefix(pos + 1);
  return sv;
}
} // namespace hippo::detail

#define HIPPO_ENUM_BEGIN(Type)                                                 \
  namespace hippo {                                                            \
  template <> struct printer<Type> {                                           \
    static ::hippo::object print(const Type &object,                           \
                                 std::uint64_t current_indent,                 \
                                 const ::hippo::configuration &) {             \
      std::string enum_type =                                                  \
          "enum " + ::hippo::detail::type_name<                                \
                        std::remove_cv_t<std::remove_reference_t<Type>>>();    \
      switch (object) {

#define HIPPO_ENUM_VALUE(Value)                                                \
  case Value: {                                                                \
    constexpr auto name = ::hippo::detail::remove_enum_namespace(#Value);      \
    return ::hippo::line{current_indent,                                       \
                         enum_type + " [" + std::string(name) + "]"};          \
  }

#define HIPPO_ENUM_END()                                                       \
  default:                                                                     \
    return ::hippo::line{current_indent, enum_type + " [unknown value]"};      \
    }                                                                          \
    }                                                                          \
    }                                                                          \
    ;                                                                          \
    }

#define HIPPO_CLASS_BEGIN(Type)                                                \
  namespace hippo {                                                            \
  template <> struct printer<Type> {                                           \
    static ::hippo::object print(const Type &object,                           \
                                 std::uint64_t current_indent,                 \
                                 const ::hippo::configuration &config) {       \
      std::list<::hippo::object> objects;

#define HIPPO_CLASS_END()                                                      \
  auto size = objects.size();                                                  \
  for (auto &o : objects) {                                                    \
    if (--size != 0) {                                                         \
      std::visit(::hippo::append_visitor{","}, o);                             \
    }                                                                          \
  }                                                                            \
  objects.emplace_front(                                                       \
      std::in_place_type<::hippo::line>, current_indent,                       \
      ::hippo::detail::type_name<                                              \
          std::remove_cv_t<std::remove_reference_t<decltype(object)>>>() +     \
          " {");                                                               \
  objects.emplace_back(std::in_place_type<::hippo::line>, current_indent,      \
                       "}");                                                   \
  return condense(objects, config);                                            \
  }                                                                            \
  }                                                                            \
  ;                                                                            \
  }

#define HIPPO_BASE(Type)                                                       \
  {                                                                            \
    static_assert(                                                             \
        std::is_base_of_v<Type, std::remove_reference_t<                       \
                                    std::remove_cv_t<decltype(object)>>>);     \
    auto subobject =                                                           \
        ::hippo::printer<Type>::print(object, current_indent + 1, config);     \
    std::visit(::hippo::prepend_visitor{"Base "}, subobject);                  \
    objects.push_back(std::move(subobject));                                   \
  }

#define HIPPO_MEMBER_EXPR(Name, Expression)                                    \
  {                                                                            \
    auto &&exprval = Expression;                                               \
    using Type = std::remove_cv_t<std::remove_reference_t<decltype(exprval)>>; \
    auto subobject =                                                           \
        ::hippo::printer<Type>::print(exprval, current_indent + 1, config);    \
    std::visit(::hippo::prepend_visitor{#Name ": "}, subobject);               \
    objects.emplace_back(std::move(subobject));                                \
  }

#define HIPPO_MEMBER(Name) HIPPO_MEMBER_EXPR(Name, object.Name)

#endif // HIPPO_DETAIL_REFLECTION_H_
