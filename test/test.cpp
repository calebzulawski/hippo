#include "hippo/hippo.h"
#include <iostream>

struct Bottom1 {
  int a = 1;
};

HIPPO_BEGIN(Bottom1)
HIPPO_MEMBER(a)
HIPPO_END()

struct Bottom2 {
  int a = 1;
  int b = 2;
};

HIPPO_BEGIN(Bottom2)
HIPPO_MEMBER(a)
HIPPO_MEMBER(b)
HIPPO_END()

struct Middle1 {
  Bottom2 a;
};

HIPPO_BEGIN(Middle1)
HIPPO_MEMBER(a)
HIPPO_END()

struct Middle2 {
  Bottom1 a;
  Bottom2 b;
};

HIPPO_BEGIN(Middle2)
HIPPO_MEMBER(a)
HIPPO_MEMBER(b)
HIPPO_END()

struct Top {
  Middle1 a;
  Middle2 b;
};

HIPPO_BEGIN(Top)
HIPPO_MEMBER(a)
HIPPO_MEMBER(b)
HIPPO_END()

int main() {
  Top t;
  auto lines = hippo::print(t, 2);
  for (const auto &line : lines)
    std::cout << line << std::endl;
  return 0;
};
