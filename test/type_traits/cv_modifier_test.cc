#include "cv_modifier.h"

#include "./../test.h"


struct Foo {};

void test_remove_const() {
  EXPECT_SAME(zstd::remove_const<int>::type, int);
  EXPECT_SAME(zstd::remove_const<const int>::type, int);
  EXPECT_SAME(zstd::remove_const<const int&>::type, const int&);
  EXPECT_SAME(zstd::remove_const<const int*>::type, const int*);
  EXPECT_SAME(zstd::remove_const<int* const>::type, int*);
  EXPECT_SAME(zstd::remove_const<const int* const>::type, const int*);
  EXPECT_SAME(zstd::remove_const<const volatile int>::type, volatile int);
  EXPECT_SAME(zstd::remove_const<Foo>::type, Foo);
  EXPECT_SAME(zstd::remove_const<const Foo>::type, Foo);
}

void test_remove_volatile() {
  EXPECT_SAME(zstd::remove_volatile<int>::type, int);
  EXPECT_SAME(zstd::remove_volatile<volatile int>::type, int);
  EXPECT_SAME(zstd::remove_volatile<volatile int&>::type, volatile int&);
  EXPECT_SAME(zstd::remove_volatile<volatile int*>::type, volatile int*);
  EXPECT_SAME(zstd::remove_volatile<int* volatile>::type, int*);
  EXPECT_SAME(zstd::remove_volatile<volatile int* volatile>::type, 
              volatile int*);
  EXPECT_SAME(zstd::remove_volatile<const volatile int>::type, const int);
  EXPECT_SAME(zstd::remove_volatile<Foo>::type, Foo);
  EXPECT_SAME(zstd::remove_volatile<volatile Foo>::type, Foo);
}

void test_remove_cv() {
  EXPECT_SAME(zstd::remove_cv<int>::type, int);
  EXPECT_SAME(zstd::remove_cv<const int>::type, int);
  EXPECT_SAME(zstd::remove_cv<volatile int>::type, int);
  EXPECT_SAME(zstd::remove_cv<const volatile int>::type, int);
  EXPECT_SAME(zstd::remove_cv<const volatile int&>::type, const volatile int&);
  EXPECT_SAME(zstd::remove_cv<const volatile int*>::type, const volatile int*);
  EXPECT_SAME(zstd::remove_cv<int* const volatile>::type, int*);
  EXPECT_SAME(zstd::remove_cv<Foo>::type, Foo);
  EXPECT_SAME(zstd::remove_cv<const volatile Foo>::type, Foo);
}

void test_add_const() {
  EXPECT_SAME(zstd::add_const<int>::type, const int);
  EXPECT_SAME(zstd::add_const<const int>::type, const int);
  EXPECT_SAME(zstd::add_const<volatile int>::type, const volatile int);
  EXPECT_SAME(zstd::add_const<int&>::type, int&);
  EXPECT_SAME(zstd::add_const<int*>::type, int* const);
  EXPECT_SAME(zstd::add_const<const int*>::type, const int* const);
  EXPECT_SAME(zstd::add_const<int* const>::type, int* const);
  EXPECT_SAME(zstd::add_const<const int* const>::type, const int* const);
  EXPECT_SAME(zstd::add_const<Foo>::type, const Foo);
  EXPECT_SAME(zstd::add_const<const Foo>::type, const Foo);
}

void test_add_volatile() {
  EXPECT_SAME(zstd::add_volatile<int>::type, volatile int);
  EXPECT_SAME(zstd::add_volatile<volatile int>::type, volatile int);
  EXPECT_SAME(zstd::add_volatile<const int>::type, const volatile int);
  EXPECT_SAME(zstd::add_volatile<int&>::type, int&);
  EXPECT_SAME(zstd::add_volatile<int*>::type, int* volatile);
  EXPECT_SAME(zstd::add_volatile<volatile int*>::type, volatile int* volatile);
  EXPECT_SAME(zstd::add_volatile<int* volatile>::type, int* volatile);
  EXPECT_SAME(zstd::add_volatile<volatile int* volatile>::type, 
              volatile int* volatile);
  EXPECT_SAME(zstd::add_volatile<Foo>::type, volatile Foo);
  EXPECT_SAME(zstd::add_volatile<volatile Foo>::type, volatile Foo);
}

void test_add_cv() {
  EXPECT_SAME(zstd::add_cv<int>::type, const volatile int);
  EXPECT_SAME(zstd::add_cv<const int>::type, const volatile int);
  EXPECT_SAME(zstd::add_cv<volatile int>::type, const volatile int);
  EXPECT_SAME(zstd::add_cv<const volatile int>::type, const volatile int);
  EXPECT_SAME(zstd::add_cv<int&>::type, int&);
  EXPECT_SAME(zstd::add_cv<const volatile int*>::type,
              const volatile int* const volatile);
  EXPECT_SAME(zstd::add_cv<int* const volatile>::type, int* const volatile);
  EXPECT_SAME(zstd::add_cv<Foo>::type, const volatile Foo);
  EXPECT_SAME(zstd::add_cv<const volatile Foo>::type, const volatile Foo);
}


int main() {
  test_remove_const();
  test_remove_volatile();
  test_remove_cv();
  test_add_const();
  test_add_volatile();
  test_add_cv();
}