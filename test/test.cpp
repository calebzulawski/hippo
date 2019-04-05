#include "hippo/hippo.h"
#include <iostream>

struct Bottom1 {
  int a[4] = {1, 2, 3, 4};
};

HIPPO_BEGIN(Bottom1)
HIPPO_MEMBER(a)
HIPPO_END()

struct Bottom2 {
  bool a = true;
  int b = -2;
  std::optional<int> c;
  std::pair<int, std::optional<int>> d;
  std::tuple<int, std::optional<int>> e;
};

HIPPO_BEGIN(Bottom2)
HIPPO_MEMBER(a)
HIPPO_MEMBER_EXPR(b, object.b < 0 ? -object.b : object.b)
HIPPO_MEMBER(c)
HIPPO_MEMBER(d)
HIPPO_MEMBER(e)
HIPPO_END()

struct Middle1 {
  std::optional<Bottom2> a{Bottom2{}};
};

HIPPO_BEGIN(Middle1)
HIPPO_MEMBER(a)
HIPPO_END()

struct Middle2 : Bottom1 {
  Bottom2 a;
};

HIPPO_BEGIN(Middle2)
HIPPO_BASE(Bottom1)
HIPPO_MEMBER(a)
HIPPO_END()

struct Top {
  std::map<int, Middle1> a{{0, Middle1()}, {1, Middle1()}};
  std::vector<Middle2> b = std::vector<Middle2>(3);
  std::string c = "c++-style\nstd::string";
  const char *d = "c-style\nstring";
};

HIPPO_BEGIN(Top)
HIPPO_MEMBER(a)
HIPPO_MEMBER(b)
HIPPO_MEMBER(c)
HIPPO_MEMBER(d)
HIPPO_END()

int main() {
  Top t;
  auto lines = hippo::print(t, ::hippo::configuration());
  for (const auto &line : lines)
    std::cout << line << std::endl;
  return 0;
};
