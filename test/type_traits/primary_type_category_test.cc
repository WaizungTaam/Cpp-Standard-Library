#include "primary_type_category.h"

#include "./../test.h"


struct Foo {};

enum En {};
enum class Ec : char {};

union Un {};


void test_is_void() {
  EXPECT(zstd::is_void<void>::value == true);
  EXPECT(zstd::is_void<int>::value == false);
  EXPECT(zstd::is_void<zstd::nullptr_t>::value == false);
  EXPECT(zstd::is_void<Foo>::value == false);
}

void test_is_null_pointer() {
  EXPECT(zstd::is_null_pointer<zstd::nullptr_t>::value == true);
  EXPECT(zstd::is_null_pointer<decltype(nullptr)>::value == true);
  EXPECT(zstd::is_null_pointer<decltype((int*)(nullptr))>::value == false);
  EXPECT(zstd::is_null_pointer<int*>::value == false);
  EXPECT(zstd::is_null_pointer<int>::value == false);
}

void test_is_integral() {
  EXPECT(zstd::is_integral<bool>::value == true);
  EXPECT(zstd::is_integral<char>::value == true);
  EXPECT(zstd::is_integral<signed char>::value == true);
  EXPECT(zstd::is_integral<unsigned char>::value == true);
  EXPECT(zstd::is_integral<wchar_t>::value == true);
  EXPECT(zstd::is_integral<char16_t>::value == true);
  EXPECT(zstd::is_integral<char32_t>::value == true);
  EXPECT(zstd::is_integral<short>::value == true);
  EXPECT(zstd::is_integral<unsigned short>::value == true);
  EXPECT(zstd::is_integral<int>::value == true);
  EXPECT(zstd::is_integral<unsigned int>::value == true);
  EXPECT(zstd::is_integral<long>::value == true);
  EXPECT(zstd::is_integral<unsigned long>::value == true);
  EXPECT(zstd::is_integral<long long>::value == true);
  EXPECT(zstd::is_integral<unsigned long long>::value == true);

  EXPECT(zstd::is_integral<const int>::value == true);
  EXPECT(zstd::is_integral<volatile int>::value == true);

  EXPECT(zstd::is_integral<float>::value == false);
  EXPECT(zstd::is_integral<double>::value == false);
  EXPECT(zstd::is_integral<long double>::value == false);
  EXPECT(zstd::is_integral<void>::value == false);
  EXPECT(zstd::is_integral<int&>::value == false);
  EXPECT(zstd::is_integral<int*>::value == false);
  EXPECT(zstd::is_integral<Foo>::value == false);
}

void test_is_floating_point() {
  EXPECT(zstd::is_floating_point<float>::value == true);
  EXPECT(zstd::is_floating_point<double>::value == true);
  EXPECT(zstd::is_floating_point<long double>::value == true);

  EXPECT(zstd::is_floating_point<const float>::value == true);
  EXPECT(zstd::is_floating_point<volatile float>::value == true);

  EXPECT(zstd::is_floating_point<int>::value == false);
  EXPECT(zstd::is_floating_point<float&>::value == false);
  EXPECT(zstd::is_floating_point<float*>::value == false);
  EXPECT(zstd::is_floating_point<Foo>::value == false);
}

void test_is_array() {
  EXPECT(zstd::is_array<int[10]>::value == true);
  EXPECT(zstd::is_array<int[]>::value == true);
  EXPECT(zstd::is_array<Foo[10]>::value == true);
  EXPECT(zstd::is_array<Foo[]>::value == true);
  EXPECT(zstd::is_array<const int[10]>::value == true);
  EXPECT(zstd::is_array<volatile int[10]>::value == true);
  EXPECT(zstd::is_array<int*[10]>::value == true);

  EXPECT(zstd::is_array<int>::value == false);
  EXPECT(zstd::is_array<int*>::value == false);
  EXPECT(zstd::is_array<Foo>::value == false);
  EXPECT(zstd::is_array<Foo*>::value == false);
}

void test_is_enum() {
  EXPECT(zstd::is_enum<En>::value == true);
  EXPECT(zstd::is_enum<Ec>::value == true);

  EXPECT(zstd::is_enum<int>::value == false);
  EXPECT(zstd::is_enum<unsigned>::value == false);
  EXPECT(zstd::is_enum<char>::value == false);
}

void test_is_union() {
  EXPECT(zstd::is_union<Un>::value == true);

  EXPECT(zstd::is_union<int>::value == false);
  EXPECT(zstd::is_union<En>::value == false);
  EXPECT(zstd::is_union<Foo>::value == false);
}

void test_is_class() {
  EXPECT(zstd::is_class<Foo>::value == true);

  EXPECT(zstd::is_class<int>::value == false);
  EXPECT(zstd::is_class<En>::value == false);
  EXPECT(zstd::is_class<Ec>::value == false);
  EXPECT(zstd::is_class<Un>::value == false);
}

void test_is_function() {
  // TODO
}

void test_is_pointer() {
  EXPECT(zstd::is_pointer<int*>::value == true);
  EXPECT(zstd::is_pointer<int**>::value == true);
  EXPECT(zstd::is_pointer<int* const>::value == true);
  EXPECT(zstd::is_pointer<int* volatile>::value == true);
  EXPECT(zstd::is_pointer<const int*>::value == true);
  EXPECT(zstd::is_pointer<volatile int*>::value == true);
  EXPECT(zstd::is_pointer<Foo*>::value == true);
  
  EXPECT(zstd::is_pointer<int>::value == false);
  EXPECT(zstd::is_pointer<int[10]>::value == false);
  EXPECT(zstd::is_pointer<zstd::nullptr_t>::value == false);
}

void test_is_lvalue_reference() {
  EXPECT(zstd::is_lvalue_reference<int&>::value == true);
  EXPECT(zstd::is_lvalue_reference<Foo&>::value == true);
  EXPECT(zstd::is_lvalue_reference<const int&>::value == true);
  EXPECT(zstd::is_lvalue_reference<volatile int&>::value == true);
  
  EXPECT(zstd::is_lvalue_reference<int>::value == false);
  EXPECT(zstd::is_lvalue_reference<Foo>::value == false);
  EXPECT(zstd::is_lvalue_reference<int&&>::value == false);
  EXPECT(zstd::is_lvalue_reference<Foo&&>::value == false);
}

void test_is_rvalue_reference() {
  EXPECT(zstd::is_rvalue_reference<int&&>::value == true);
  EXPECT(zstd::is_rvalue_reference<Foo&&>::value == true);
  EXPECT(zstd::is_rvalue_reference<const int&&>::value == true);
  EXPECT(zstd::is_rvalue_reference<volatile int&&>::value == true);
  
  EXPECT(zstd::is_rvalue_reference<int>::value == false);
  EXPECT(zstd::is_rvalue_reference<Foo>::value == false);
  EXPECT(zstd::is_rvalue_reference<int&>::value == false);
  EXPECT(zstd::is_rvalue_reference<Foo&>::value == false);
}

void test_is_member_object_pointer() {
  // TODO
}

void test_is_member_function_pointer() {
  // TODO
}


int main() {
  test_is_void();
  test_is_null_pointer();
  test_is_integral();
  test_is_floating_point();
  test_is_array();
  test_is_enum();
  test_is_union();
  test_is_class();
  test_is_function();
  test_is_pointer();
  test_is_lvalue_reference();
  test_is_rvalue_reference();
  test_is_member_object_pointer();
  test_is_member_function_pointer();
}
