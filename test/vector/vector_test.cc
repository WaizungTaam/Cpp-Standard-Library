#include "vector.h"

#include "./../test.h"


void test_default_constructor() {
  zstd::vector<int> a;
}

void test_push_back() {
  zstd::vector<int> a;
  for (int i = 0; i < 100; ++i) {
    a.push_back(i);
  }
  for (int i = 0; i < 100; ++i) {
    REQUIRE(a[i] == i);
  }
}

int main() {
  test_default_constructor();
  test_push_back();
}