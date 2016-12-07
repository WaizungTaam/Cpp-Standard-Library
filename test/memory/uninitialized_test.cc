#include "uninitialized.h"

#include "temporary_buffer.h"

#include "./../test.h"


class Foo {
public:
  Foo() : i_(0), f_(0.0) {}
  Foo(int i, float f) : i_(i), f_(f) {}
  bool operator==(const Foo& other) {
    return this->i_ == other.i_ && this->f_ == other.f_;
  }
private:
  int i_;
  float f_;
};

void test_uninitialized_copy() {
  int a_int[100];
  for (int i = 0; i < 100; ++i) {
    a_int[i] = i;
  }
  auto p_int = zstd::get_temporary_buffer<int>(100);
  zstd::uninitialized_copy(a_int, a_int + p_int.second, p_int.first);
  for (int i = 0; i < p_int.second; ++i) {
    REQUIRE(a_int[i] == *(p_int.first + i));
  }
  zstd::return_temporary_buffer(p_int.first);
  
  Foo a_foo[100];
  for (int i = 0; i < 100; ++i) {
    a_foo[i] = Foo(i, i / 2.0);
  }
  auto p_foo = zstd::get_temporary_buffer<Foo>(100);
  zstd::uninitialized_copy(a_foo, a_foo + p_foo.second, p_foo.first);
  for (int i = 0; i < p_foo.second; ++i) {
    REQUIRE(a_foo[i] == *(p_foo.first + i));
  }
  zstd::return_temporary_buffer(p_foo.first);
}

void test_uninitialized_fill() {
  auto p_int = zstd::get_temporary_buffer<int>(100);
  zstd::fill(p_int.first, p_int.first + p_int.second, 7);
  for (int i = 0; i < p_int.second; ++i) {
    REQUIRE(*(p_int.first + i) == 7);
  }
  zstd::return_temporary_buffer(p_int.first);
  
  auto p_foo = zstd::get_temporary_buffer<Foo>(100);
  zstd::fill(p_foo.first, p_foo.first + p_foo.second, Foo(7, 1.75));
  for (int i = 0; i < p_foo.second; ++i) {
    REQUIRE(*(p_foo.first + i) == Foo(7, 1.75));
  }
  zstd::return_temporary_buffer(p_foo.first);
}

void test_uninitialized_fill_n() {
  auto p_int = zstd::get_temporary_buffer<int>(100);
  zstd::fill_n(p_int.first, p_int.second, 7);
  for (int i = 0; i < p_int.second; ++i) {
    REQUIRE(*(p_int.first + i) == 7);
  }
  zstd::return_temporary_buffer(p_int.first);
  
  auto p_foo = zstd::get_temporary_buffer<Foo>(100);
  zstd::fill_n(p_foo.first, p_foo.second, Foo(7, 1.75));
  for (int i = 0; i < p_foo.second; ++i) {
    REQUIRE(*(p_foo.first + i) == Foo(7, 1.75));
  }
}


int main() {
  test_uninitialized_copy();
  test_uninitialized_fill();
  test_uninitialized_fill_n();
}
