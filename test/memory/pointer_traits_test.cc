#include "pointer_traits.h"

#include "./../test.h"


void test_trivial_pointer() {
  REQUIRE_SAME(zstd::pointer_traits<int*>::pointer, int*);
  REQUIRE_SAME(zstd::pointer_traits<int*>::element_type, int);
  REQUIRE_SAME(zstd::pointer_traits<int*>::difference_type, zstd::ptrdiff_t);
  REQUIRE_SAME(zstd::pointer_traits<int*>::rebind<float>::other, float*);
  int i = 0;
  REQUIRE(zstd::pointer_traits<int*>::pointer_to(i) == &i);
}

void test_void_pointer() {
  REQUIRE_SAME(zstd::pointer_traits<void*>::pointer, void*);
  EXPECT_SAME(zstd::pointer_traits<void*>::element_type, void);
  REQUIRE_SAME(zstd::pointer_traits<void*>::difference_type, zstd::ptrdiff_t);
  REQUIRE_SAME(zstd::pointer_traits<void*>::rebind<int>::other, int*);
}

void test_defined_pointer() {
  // TODO
}

int main() {
  test_trivial_pointer();
  test_void_pointer();
}