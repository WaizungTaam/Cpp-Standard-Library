#include "addressof.h"

#include "../test.h"


struct Foo {};

struct UnRef {
  Foo* operator&() { return nullptr; }
};

void test_addressof() {
  int i = 0;
  int& i_ref = i;
  int j = 0;
  Foo f;

  EXPECT(&i == &i_ref);
  EXPECT(&i != &j);
  REQUIRE(zstd::addressof(i) == &i);
  REQUIRE(zstd::addressof(i_ref) == zstd::addressof(i));
  REQUIRE(zstd::addressof(f) == &f);
}

void test_addressof_overloaded() {
  UnRef u;

  EXPECT(&u == nullptr);
  REQUIRE(zstd::addressof(u) != nullptr);
}


int main() {
  test_addressof();
  test_addressof_overloaded();
}