#ifndef HIPPO_DETAIL_STRINGS_H_
#define HIPPO_DETAIL_STRINGS_H_

#include "base.h"
#include "formatter.h"
#include <iterator>
#include <sstream>
#include <utility>

namespace hippo::detail {

template <typename String, typename Base> struct stringlike {
  using format_type = hippo::no_format;
  static ::hippo::object print(const String &s, std::uint64_t current_indent,
                               const ::hippo::configuration &config,
                               const format_type & = format_type()) {
    std::list<std::string> lines;
    std::istringstream ss(s);
    std::string l;
    while (std::getline(ss, l))
      lines.emplace_back(l);
    if (lines.size() == 0) {
      return ::hippo::object{std::in_place_type<::hippo::line>, current_indent,
                             std::string(Base::prefix) + " [empty]"};
    } else {
      std::list<::hippo::line> retlines;
      retlines.emplace_front(current_indent, std::string(Base::prefix) + " [");
      for (const auto &l : lines)
        retlines.emplace_back(current_indent + 1, l);
      retlines.emplace_back(current_indent, "]");
      return (lines.size() == 1)
                 ? condense(retlines, config)
                 : ::hippo::object{std::in_place_type<std::list<::hippo::line>>,
                                   retlines};
    }
  }
};

} // namespace hippo::detail

#endif // HIPPO_DETAIL_STRINGS_H_
