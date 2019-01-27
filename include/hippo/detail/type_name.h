#ifndef HIPPO_DETAIL_TYPE_NAME_H_
#define HIPPO_DETAIL_TYPE_NAME_H_

#include <cstdlib>
#include <cxxabi.h>
#include <string>

namespace hippo::detail {

template <typename T> std::string type_name_impl() {
  int status;
  char *name = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
  if (status != 0) {
    return "(could not determine type name)";
  } else {
    std::string s(name);
    std::free(name);
    return s;
  }
}

template <typename T> std::string type_name() {
  static std::string cached = type_name_impl<T>();
  return cached;
}

} // namespace hippo::detail

#endif // HIPPO_DETAIL_TYPE_NAME_H_
