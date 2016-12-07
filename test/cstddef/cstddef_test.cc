#include "cstddef.h"

#include "../test.h"


void null_test() {
  char* p = NULL;
  EXPECT(p == nullptr);
}

void size_t_test() {
  EXPECT(zstd::size_t(0) < zstd::size_t(-1));
}

void ptrdiff_t_test() {
  EXPECT(zstd::ptrdiff_t(0) > zstd::ptrdiff_t(-1));
}

struct Foo {
  char c;
  int i;
  char s[10];
};

void offsetof_test() {
  EXPECT(zstd::offsetof(Foo, c) == 0);
}

void nullptr_t_test() {
  zstd::nullptr_t p;
  EXPECT(p == nullptr);
}

void max_align_t_test() {
  EXPECT(alignof(zstd::max_align_t) == 8  || alignof(zstd::max_align_t) == 16);
}


int main() {
  null_test();
  size_t_test();
  ptrdiff_t_test();
  offsetof_test();
  nullptr_t_test();
  max_align_t_test();
}