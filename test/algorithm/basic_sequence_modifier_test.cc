#include "basic_sequence_modifier.h"

#include "../test.h"


void test_copy() {
  int a1[1000], a2[1000];
  for (int i = 0; i < 1000; ++i) {
    a1[i] = i;
  }
  zstd::copy(a1, a1 + 1000, a2);
  for (int i = 0; i < 5; ++i) {
    REQUIRE(a1[i] == a2[i]);
  }
}

void test_fill() {
  int a[1000];
  zstd::fill(a, a + 1000, 7);
  for (int i = 0; i < 1000; ++i) {
    REQUIRE(a[i] == 7);
  }
}

void test_fill_n() {
  int a[1000];
  zstd::fill_n(a, 1000, 7);
  for (int i = 0; i < 1000; ++i) {
    REQUIRE(a[i] == 7);
  }
}


int main() {
  test_copy();
  test_fill();
  test_fill_n();
}