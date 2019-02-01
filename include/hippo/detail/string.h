#ifndef HIPPO_DETAIL_STRING_H_
#define HIPPO_DETAIL_STRING_H_

#include "base.h"
#include <list>
#include <sstream>
#include <string>

namespace hippo {

template <> struct printer<std::string> {
  static std::list<::hippo::line> print(const std::string &s,
                                        std::uint64_t current_indent,
                                        const ::hippo::configuration &) {
    std::list<::hippo::line> lines;
    lines.emplace_back(current_indent, "<--");
    std::istringstream ss(s);
    std::string l;
    while (std::getline(ss, l))
      lines.emplace_back(current_indent + 1, l);
    lines.emplace_back(current_indent, "-->");
    return lines;
  }
};

template <> struct printer<const char *> {
  static std::list<::hippo::line> print(const char *s,
                                        std::uint64_t current_indent,
                                        const ::hippo::configuration &config) {
    return ::hippo::printer<std::string>::print(std::string(s), current_indent,
                                                config);
  }
};

} // namespace hippo

#endif // HIPPO_DETAIL_STRING_H_
