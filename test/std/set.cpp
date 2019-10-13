#include "hippo/std/set.h"
#include "arraylike.h"
#include "hippo/hippo.h"
#include <set>

TEST_ARRAYLIKE("set", "std::set", std::set)
TEST_ARRAYLIKE("multiset", "std::multiset", std::multiset<int>)
