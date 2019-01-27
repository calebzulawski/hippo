#ifndef HIPPO_DETAIL_NUMBERS_H_
#define HIPPO_DETAIL_NUMBERS_H_

#include "base.h"

namespace hippo {

template <typename T>
struct stringifier<T, std::enable_if_t<std::is_arithmetic<T>::value, T>> {
  static std::string stringify(const T &t) { return std::to_string(t); }
};

} // namespace hippo

#endif // HIPPO_DETAIL_NUMBERS_H_
