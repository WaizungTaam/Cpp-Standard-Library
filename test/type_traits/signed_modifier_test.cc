#include "signed_modifier.h"

#include "./../test.h"


void test_make_signed() {
  REQUIRE_SAME(zstd::make_signed<unsigned int>::type, signed int);
  // TODO
}

void test_make_unsigned() {
  // TODO
}


int main() {
  test_make_signed();
  test_make_unsigned();
}