#include "test.h"

int main() {
  REQUIRE(1 == 1);
  EXPECT(1 == 1);
  EXPECT(1 == 2);
  EXPECT(1 == 3);
  EXPECT_SAME(int, int);
  EXPECT_SAME(int, float);
  REQUIRE_SAME(double, double);
  REQUIRE(1 == 2);
}