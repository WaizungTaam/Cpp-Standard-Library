#include "type_traits_base.h"

#include "./../test.h"


void test_integral_constant() {
	typedef zstd::integral_constant<bool, true> bool_constant;
	typedef zstd::integral_constant<int, 1> int_constant;

	EXPECT(bool_constant::value == true);
	EXPECT(int_constant::value == 1);

  EXPECT_SAME(bool_constant::value_type, bool);
  EXPECT_SAME(int_constant::value_type, int);

  EXPECT_SAME(bool_constant::type, bool_constant);
  EXPECT_SAME(int_constant::type, int_constant);

  bool_constant bool_true;
  int_constant int_1;
	EXPECT(bool_true() == true);
	EXPECT(int_1() == 1);
}

void test_true_type() {
	EXPECT(zstd::true_type::value == true);
	EXPECT_SAME(zstd::true_type::value_type, bool);
	EXPECT_SAME(zstd::true_type::type, zstd::true_type);
	zstd::true_type true_obj;
	EXPECT(true_obj() == true);
}

void test_false_type() {
	EXPECT(zstd::false_type::value == false);
	EXPECT_SAME(zstd::false_type::value_type, bool);
	EXPECT_SAME(zstd::false_type::type, zstd::false_type);
	zstd::false_type false_obj;
	EXPECT(false_obj() == false);
}


int main() {
	test_integral_constant();
	test_true_type();
	test_false_type();
}