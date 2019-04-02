#ifndef HIPPO_DETAIL_REFLECTION_H_
#define HIPPO_DETAIL_REFLECTION_H_

#include "base.h"
#include "type_name.h"
#include <list>
#include <type_traits>

#define HIPPO_BEGIN(Type)                                                      \
  namespace hippo {                                                            \
  template <> struct printer<Type> {                                           \
    static ::hippo::object print(const Type &object,                           \
                                 std::uint64_t current_indent,                 \
                                 const ::hippo::configuration &config) {       \
      std::list<::hippo::object> objects;

#define HIPPO_END()                                                            \
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
    using Type =                                                               \
        std::remove_cv_t<std::remove_reference_t<decltype(Expression)>>;       \
    auto subobject = ::hippo::printer<Type>::print(                            \
        (Expression), current_indent + 1, config);                             \
    std::visit(::hippo::prepend_visitor{#Name ": "}, subobject);               \
    objects.emplace_back(std::move(subobject));                                \
  }

#define HIPPO_MEMBER(Name) HIPPO_MEMBER_EXPR(Name, object.Name)

#endif // HIPPO_DETAIL_REFLECTION_H_
