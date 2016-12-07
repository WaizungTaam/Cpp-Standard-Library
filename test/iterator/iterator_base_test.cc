#include "iterator_base.h"

#include "./../test.h"


void test_iterator_tag() {
  zstd::input_iterator_tag input_tag;
  zstd::output_iterator_tag output_tag;
  zstd::forward_iterator_tag forward_tag;
  zstd::bidirectional_iterator_tag bidirectional_tag;
  zstd::random_access_iterator_tag random_access_tag;
  
  REQUIRE_BASE_OF(zstd::input_iterator_tag, 
                  zstd::forward_iterator_tag);
  REQUIRE_BASE_OF(zstd::forward_iterator_tag,
                  zstd::bidirectional_iterator_tag);
  REQUIRE_BASE_OF(zstd::bidirectional_iterator_tag,
                  zstd::random_access_iterator_tag);
}

void test_input_iterator() {
  typedef zstd::input_iterator<float, int> input_it;
  REQUIRE_SAME(input_it::iterator_category, zstd::input_iterator_tag);
  EXPECT_SAME(input_it::value_type, float);
  EXPECT_SAME(input_it::difference_type, int);
  EXPECT_SAME(input_it::pointer, float*);
  EXPECT_SAME(input_it::reference, float&);
}

void test_output_iterator() {
  typedef zstd::output_iterator output_it;
  REQUIRE_SAME(output_it::iterator_category, zstd::output_iterator_tag);
  EXPECT_SAME(output_it::value_type, void);
  EXPECT_SAME(output_it::difference_type, void);
  EXPECT_SAME(output_it::pointer, void);
  EXPECT_SAME(output_it::reference, void);
}

void test_forward_iterator() {
  typedef zstd::forward_iterator<float, int> forward_it;
  REQUIRE_SAME(forward_it::iterator_category, zstd::forward_iterator_tag);
  EXPECT_SAME(forward_it::value_type, float);
  EXPECT_SAME(forward_it::difference_type, int);
  EXPECT_SAME(forward_it::pointer, float*);
  EXPECT_SAME(forward_it::reference, float&);
}

void test_bidirectional_iterator() {
  typedef zstd::bidirectional_iterator<float, int> bidirectional_it;
  REQUIRE_SAME(bidirectional_it::iterator_category, 
               zstd::bidirectional_iterator_tag);
  EXPECT_SAME(bidirectional_it::value_type, float);
  EXPECT_SAME(bidirectional_it::difference_type, int);
  EXPECT_SAME(bidirectional_it::pointer, float*);
  EXPECT_SAME(bidirectional_it::reference, float&);
}

void test_random_access_iterator() {
  typedef zstd::random_access_iterator<float, int> random_access_it;
  REQUIRE_SAME(random_access_it::iterator_category,
               zstd::random_access_iterator_tag);
  EXPECT_SAME(random_access_it::value_type, float);
  EXPECT_SAME(random_access_it::difference_type, int);
  EXPECT_SAME(random_access_it::pointer, float*);
  EXPECT_SAME(random_access_it::reference, float&);
}

void test_iterator() {
  zstd::iterator<zstd::input_iterator_tag, float> it1;
  zstd::iterator<zstd::input_iterator_tag, float, int> it2;
  zstd::iterator<zstd::input_iterator_tag, float, int, float*> it3;
  zstd::iterator<zstd::input_iterator_tag, float, int, float, float&> it4;
}


int main() {
  test_iterator_tag();
  test_input_iterator();
  test_output_iterator();
  test_forward_iterator();
  test_bidirectional_iterator();
  test_random_access_iterator();
  test_iterator();
}
