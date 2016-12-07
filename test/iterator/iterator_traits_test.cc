#include "iterator_traits.h"

#include "iterator_base.h"

#include "../test.h"


void test_iterator_traits() {
  typedef zstd::iterator<zstd::input_iterator_tag, float, long, float*, float&>
          it;
  REQUIRE_SAME(zstd::iterator_traits<it>::iterator_category, 
               zstd::input_iterator_tag);
  REQUIRE_SAME(zstd::iterator_traits<it>::value_type, float);
  REQUIRE_SAME(zstd::iterator_traits<it>::difference_type, long);
  REQUIRE_SAME(zstd::iterator_traits<it>::pointer, float*);
  REQUIRE_SAME(zstd::iterator_traits<it>::reference, float&);
}

void test_iterator_traits_pointer() {
  REQUIRE_SAME(zstd::iterator_traits<int*>::iterator_category, 
               zstd::random_access_iterator_tag);
  REQUIRE_SAME(zstd::iterator_traits<int*>::value_type, int);
  REQUIRE_SAME(zstd::iterator_traits<int*>::difference_type, zstd::ptrdiff_t);
  REQUIRE_SAME(zstd::iterator_traits<int*>::pointer, int*);
  REQUIRE_SAME(zstd::iterator_traits<int*>::reference, int&);
}

void test_iterator_traits_const_pointer() {
  REQUIRE_SAME(zstd::iterator_traits<const int*>::iterator_category, 
               zstd::random_access_iterator_tag);
  REQUIRE_SAME(zstd::iterator_traits<const int*>::value_type, int);
  REQUIRE_SAME(zstd::iterator_traits<const int*>::difference_type, 
               zstd::ptrdiff_t);
  REQUIRE_SAME(zstd::iterator_traits<const int*>::pointer, const int*);
  REQUIRE_SAME(zstd::iterator_traits<const int*>::reference, const int&);
}


int main() {
  test_iterator_traits();
  test_iterator_traits_pointer();
  test_iterator_traits_const_pointer();
}