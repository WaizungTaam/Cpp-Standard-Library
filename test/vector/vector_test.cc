#include "vector.h"

#define ZTEST_PRINT
#include "./../test.h"


class Foo {
  friend bool operator==(const Foo&, const Foo&);
public:
  Foo() : i_(0), f_(0) {}
  Foo(int i, float f) : i_(i), f_(f) {}

private:
  int i_;
  float f_;
};

bool operator==(const Foo& x, const Foo& y) {
  return x.i_ == y.i_ && x.f_ == y.f_;
}
bool operator!=(const Foo& x, const Foo& y) {
  return !(x == y);
}

void test_default_constructor() {
  zstd::vector<int> v_int;
  REQUIRE(v_int.size() == 0);

  zstd::vector<Foo> v_foo;
  REQUIRE(v_foo.size() == 0);
}

void test_default_alloc_constructor() {

}

void test_default_n_constructor() {
  zstd::vector<int> v_int(100);
  REQUIRE(v_int.size() == 100);
  for (int i = 0; i < v_int.size(); ++i) {
    REQUIRE(v_int[i] == int());
  }

  zstd::vector<Foo> v_foo(100);
  REQUIRE(v_foo.size() == 100);
  for (int i = 0; i < v_foo.size(); ++i) {
    REQUIRE(v_foo[i] == Foo());
  }
}

void test_default_n_alloc_constructor() {

}

void test_fill_n_constructor() {
  zstd::vector<int> v_int(100, 7);
  REQUIRE(v_int.size() == 100);
  for (int i = 0; i < v_int.size(); ++i) {
    REQUIRE(v_int[i] == 7);
  }

  Foo foo(7, 1.75);
  zstd::vector<Foo> v_foo(100, foo);
  REQUIRE(v_foo.size() == 100);
  for (int i = 0; i < v_foo.size(); ++i) {
    REQUIRE(v_foo[i] == foo);
  }
}

void test_fill_n_alloc_constructor() {

}

void test_range_constructor() {
  zstd::vector<int> v_int_src(100);
  for (int i = 0; i < 100; ++i) {
    v_int_src[i] = i;
  }
  zstd::vector<int> v_int(v_int_src.begin(), v_int_src.end());
  REQUIRE(v_int.size() == v_int_src.size());
  for (int i = 0; i < v_int.size(); ++i) {
    v_int[i] == v_int_src[i];
  }

  zstd::vector<Foo> v_foo_src(100);
  for (int i = 0; i < 100; ++i) {
    Foo foo(i, i / 2.0);
    v_foo_src[i] = foo;
  }
  zstd::vector<Foo> v_foo(v_foo_src.begin(), v_foo_src.end());
  REQUIRE(v_foo.size() == v_foo_src.size());
  for (int i = 0; i < v_foo.size(); ++i) {
    v_foo[i] == v_foo_src[i];
  }
}

void test_range_alloc_constructor() {

}

void test_init_list_constructor() {
  // zstd::vector<int> v_int = { 0, 1, 2, 3, 4 };
  // REQUIRE(v_int.size() == 5);
  // for (int i = 0; i < v_int.size(); ++i) {
  //   REQUIRE(v_int[i] == i);
  // }

  // zstd::vector<Foo> v_foo = { 
  //   Foo(0, 0.0), Foo(1, 0.5), Foo(2, 1.0), Foo(3, 1.5), Foo(4, 2.0) };
  // REQUIRE(v_foo.size() == 5);
  // for (int i = 0; i < v_foo.size(); ++i) {
  //   REQUIRE(v_foo[i] = Foo(i, i / 2.0));
  // }
}

void test_init_list_alloc_constructor() {

}

void test_copy_constructor() {

}

void test_copy_alloc_constructor() {

}

void test_move_contructor() {

}

void test_move_alloc_constructor() {

}

void test_copy_assignment_operator() {

}

void test_move_assignment_operator() {

}

void test_init_list_assignment_operator() {

}

void test_destructor() {

}

void test_fill_n_assign() {
  zstd::vector<int> v_int(100);
  for (int i = 0; i < v_int.size(); ++i) {
    v_int[i] = i;
  }
  v_int.assign(50, 7);
  REQUIRE(v_int.size() == 50);
  for (int i = 0; i < v_int.size(); ++i) {
    REQUIRE(v_int[i] == 7);
  }
  v_int.assign(150, 15);
  REQUIRE(v_int.size() == 150);
  for (int i = 0; i < v_int.size(); ++i) {
    REQUIRE(v_int[i] == 15);
  }

  zstd::vector<Foo> v_foo(100);
  for (int i = 0; i < 100; ++i) {
    Foo foo(i, i / 2.0);
    v_foo[i] = foo;
  }
  Foo foo(7, 3.5);
  v_foo.assign(50, foo);
  REQUIRE(v_foo.size() == 50);
  for (int i = 0; i < v_foo.size(); ++i) {
    REQUIRE(v_foo[i] == foo);
  }
  foo = Foo(15, 7.5);
  v_foo.assign(150, foo);
  REQUIRE(v_foo.size() == 150);
  for (int i = 0; i < v_foo.size(); ++i) {
    REQUIRE(v_foo[i] == foo);
  }
}

void test_range_assign() {

}

void test_init_list_assign() {

}

void test_get_allocator() {

}

void test_begin() {
  zstd::vector<int> v_int(10);
  for (int i = 0; i < v_int.size(); ++i) {
    v_int[i] = i;
  }
  REQUIRE_SAME(decltype(v_int.begin()), zstd::vector<int>::iterator);
  REQUIRE(*v_int.begin() == v_int[0]);

  zstd::vector<Foo> v_foo(10);
  for (int i = 0; i < v_foo.size(); ++i) {
    Foo foo(i, i / 2.0);
    v_foo[i] = foo;
  }
  REQUIRE_SAME(decltype(v_foo.begin()), zstd::vector<Foo>::iterator);
  REQUIRE(*v_foo.begin() == v_foo[0]);
}

void test_const_begin() {
  const zstd::vector<int> v_int(10, 7);
  REQUIRE_SAME(decltype(v_int.begin()), zstd::vector<int>::const_iterator);
  REQUIRE(*v_int.begin() == v_int[0]);

  const zstd::vector<Foo> v_foo(10, Foo(7, 3.5));
  REQUIRE_SAME(decltype(v_foo.begin()), zstd::vector<Foo>::const_iterator);
  REQUIRE(*v_foo.begin() == Foo(7, 3.5));
}

void test_cbegin() {
  zstd::vector<int> v_int(10);
  for (int i = 0; i < v_int.size(); ++i) {
    v_int[i] = i;
  }
  REQUIRE_SAME(decltype(v_int.cbegin()), zstd::vector<int>::const_iterator);
  REQUIRE(*v_int.begin() == v_int[0]);

  zstd::vector<Foo> v_foo(10);
  for (int i = 0; i < v_foo.size(); ++i) {
    Foo foo(i, i / 2.0);
    v_foo[i] = foo;
  }
  REQUIRE_SAME(decltype(v_foo.cbegin()), zstd::vector<Foo>::const_iterator);
  REQUIRE(*v_foo.cbegin() == v_foo[0]);
}

void test_end() {

}

void test_const_end() {

}

void test_cend() {

}

void test_rbegin() {

}

void test_const_rbegin() {

}

void test_rend() {

}

void test_const_rend() {

}

void test_crend() {

}

void test_empty() {
  zstd::vector<int> v_int;
  REQUIRE(v_int.empty());
  v_int.push_back(1);
  REQUIRE(!v_int.empty());

  zstd::vector<Foo> v_foo;
  REQUIRE(v_foo.empty());
  v_foo.push_back(Foo(1, 0.5));
  REQUIRE(!v_foo.empty());
}

void test_size() {
  zstd::vector<int> v_int;
  REQUIRE_SAME(decltype(v_int.size()), zstd::vector<int>::size_type);
}

void test_max_size() {

}

void test_capacity() {

}

void test_reserve() {

}

void test_shrink_to_fit() {
  // zstd::vector<int> v_int;
  // for (int i = 0; i < 100; ++i) {
  //   v_int.push_back(i);
  // }
  // EXPECT(v_int.capacity() == 128);
  // v_int.shrink_to_fit();
  // REQUIRE(v_int.capacity() == v_int.size());

  // zstd::vector<Foo> v_foo;
  // for (int i = 0; i < 100; ++i) {
  //   v_foo.push_back(Foo(i, i / 2.0));
  // }
  // EXPECT(v_foo.capacity() == 128);
  // v_foo.shrink_to_fit();
  // REQUIRE(v_foo.capacity() == v_int.size());
}

void test_index_access() {
  zstd::vector<int> v_int(100);
  for (int i = 0; i < 100; ++i) {
    v_int[i] = i;
    REQUIRE(v_int[i] == i);
    REQUIRE_SAME(decltype(v_int[i]), zstd::vector<int>::reference);
  }
  v_int[0] = 100;
  REQUIRE(v_int[0] == 100);
  v_int[v_int.size()];

  zstd::vector<Foo> v_foo(100);
  for (int i = 0; i < 100; ++i) {
    v_foo[i] = Foo(i, i / 2.0);
    REQUIRE(v_foo[i] == Foo(i, i / 2.0));
    REQUIRE_SAME(decltype(v_foo[i]), zstd::vector<Foo>::reference);
  }
  v_foo[0] = Foo(100, 50.0);
  REQUIRE(v_foo[0] == Foo(100, 50.0));
  v_foo[v_foo.size()];
}

void test_const_index_access() {
  const zstd::vector<int> v_int(100, 1);
  for (int i = 0; i < v_int.size(); ++i) {
    REQUIRE(v_int[i] == 1);
    REQUIRE_SAME(decltype(v_int[i]), zstd::vector<int>::const_reference);
  }
  v_int[v_int.size()];

  const zstd::vector<Foo> v_foo(100, Foo(1, 0.5));
  for (int i = 0; i < v_foo.size(); ++i) {
    REQUIRE(v_foo[i] == Foo(1, 0.5));
    REQUIRE_SAME(decltype(v_foo[i]), zstd::vector<Foo>::const_reference);
  }
}

void test_at() {

}

void test_const_at() {

}

void test_front() {

}

void test_const_front() {

}

void test_back() {

}

void test_const_back() {

}

void test_data() {

}

void test_const_data() {

}

void test_clear() {
  zstd::vector<int> v_int;
  for (int i = 0; i < 100; ++i) {
    v_int.push_back(i);
  }
  REQUIRE(!v_int.empty());
  v_int.clear();
  REQUIRE(v_int.empty());

  zstd::vector<Foo> v_foo;
  for (int i = 0; i < 100; ++i) {
    v_foo.push_back(Foo(i, i / 2.0));
  }
  REQUIRE(!v_foo.empty());
  v_foo.clear();
  REQUIRE(v_foo.empty());
}

void test_copy_insert() {
  zstd::vector<int> v_int(100);
  for (int i = 0; i < v_int.size(); ++i) {
    v_int[i] = i;
  }
  REQUIRE(v_int.size() == 100);
  int ii = 100;
  v_int.insert(v_int.end(), ii);
  REQUIRE(v_int.size() == 101);
  for (int i = 0; i < v_int.size(); ++i) {
    REQUIRE(v_int[i] == i);
  }
  ii = 101;
  v_int.insert(v_int.begin() + 50, ii);
  REQUIRE(v_int.size() == 102);
  for (int i = 0; i < 50; ++i) {
    REQUIRE(v_int[i] == i);
  }
  REQUIRE(v_int[50] == ii);
  for (int i = 51; i < v_int.size(); ++i) {
    REQUIRE(v_int[i] == i - 1);
  }
  ii = 102;
  v_int.insert(v_int.begin(), ii);
  REQUIRE(v_int.size() == 103);
  REQUIRE(v_int[0] == ii);
  for (int i = 1; i < 51; ++i) {
    REQUIRE(v_int[i] == i - 1);
  }
  REQUIRE(v_int[51] == 101);
  for (int i = 52; i < v_int.size(); ++i) {
    REQUIRE(v_int[i] == i - 2);
  }
}

void test_move_insert() {

}

void test_insert_n() {

}

void test_range_insert() {

}

void test_emplace() {

}

void test_erase() {
  zstd::vector<int> v_int(100);
  for (int i = 0; i < 100; ++i) {
    v_int[i] = i;
  }
  REQUIRE(v_int.size() == 100);
  v_int.erase(v_int.end() - 1);
  REQUIRE(v_int.size() == 99);
  for (int i = 0; i < v_int.size(); ++i) {
    REQUIRE(v_int[i] == i);
  }
  v_int.erase(v_int.begin() + 50);
  REQUIRE(v_int.size() == 98);
  for (int i = 0; i < 50; ++i) {
    REQUIRE(v_int[i] == i);
  }
  for (int i = 50; i < v_int.size(); ++i) {
    REQUIRE(v_int[i] == i + 1);
  }
  v_int.erase(v_int.begin());
  REQUIRE(v_int.size() == 97);
  for (int i = 0; i < 49; ++i) {
    REQUIRE(v_int[i] == i + 1);
  }
  for (int i = 49; i < v_int.size(); ++i) {
    REQUIRE(v_int[i] == i + 2);
  }

  zstd::vector<Foo> v_foo(100);
  for (int i = 0; i < 100; ++i) {
    v_foo[i] = Foo(i, i / 2.0);
  }
  REQUIRE(v_foo.size() == 100);
  v_foo.erase(v_foo.end() - 1);
  REQUIRE(v_foo.size() == 99);
  for (int i = 0; i < v_foo.size(); ++i) {
    REQUIRE(v_foo[i] == Foo(i, i / 2.0));
  }
  v_foo.erase(v_foo.begin() + 50);
  REQUIRE(v_foo.size() == 98);
  for (int i = 0; i < 50; ++i) {
    REQUIRE(v_foo[i] == Foo(i, i / 2.0));
  }
  for (int i = 50; i < v_foo.size(); ++i) {
    REQUIRE(v_foo[i] == Foo(i + 1, (i + 1) / 2.0));
  }
  v_foo.erase(v_foo.begin());
  REQUIRE(v_foo.size() == 97);
  for (int i = 0; i < 49; ++i) {
    REQUIRE(v_foo[i] == Foo(i + 1, (i + 1) / 2.0));
  }
  for (int i = 49; i < v_foo.size(); ++i) {
    REQUIRE(v_foo[i] == Foo(i + 2, (i + 2) / 2.0));
  }
}

void test_range_erase() {

}

void test_copy_push_back() {
  zstd::vector<int> v_int;
  for (int i = 0; i < 100; ++i) {
    REQUIRE(v_int.size() == i);
    v_int.push_back(i);
    REQUIRE(v_int[i] == i);
    REQUIRE(v_int.size() == i + 1);
  }

  zstd::vector<Foo> v_foo;
  for (int i = 0; i < 100; ++i) {
    REQUIRE(v_foo.size() == i);
    Foo foo(i, i / 2.0);
    v_foo.push_back(foo);
    REQUIRE(v_foo[i] == foo);
    REQUIRE(v_foo.size() == i + 1);
  }
}

void test_move_push_back() {
  zstd::vector<int> v_int;
  for (int i = 0; i < 100; ++i) {
    REQUIRE(v_int.size() == i);
    v_int.push_back(7);
    REQUIRE(v_int[i] == 7);
    REQUIRE(v_int.size() == i + 1);
  }

  zstd::vector<Foo> v_foo;
  for (int i = 0; i < 100; ++i) {
    REQUIRE(v_foo.size() == i);
    v_foo.push_back(Foo(i, i / 2.0));
    REQUIRE(v_foo[i] == Foo(i, i / 2.0));
    REQUIRE(v_foo.size() == i + 1);
  }
}

void test_emplace_back() {
  zstd::vector<int> v_int;
  for (int i = 0; i < 100; ++i) {
    REQUIRE(v_int.size() == i);
    v_int.emplace_back(i);
    REQUIRE(v_int[i] == i);
    REQUIRE(v_int.size() == i + 1);
  }

  zstd::vector<Foo> v_foo;
  for (int i = 0; i < 50; ++i) {
    REQUIRE(v_foo.size() == i);
    v_foo.emplace_back(i, i / 2.0);
    REQUIRE(v_foo[i] == Foo(i, i / 2.0));
    REQUIRE(v_foo.size() == i + 1);
  }
  for (int i = 50; i < 100; ++i) {
    REQUIRE(v_foo.size() == i);
    v_foo.emplace_back(Foo(i, i / 2.0));
    REQUIRE(v_foo[i] == Foo(i, i / 2.0));
    REQUIRE(v_foo.size() == i + 1);
  }
}

void test_pop_back() {
  zstd::vector<int> v_int;
  for (int i = 0; i < 100; ++i) {
    v_int.push_back(i);
  }
  REQUIRE(v_int.size() == 100);
  REQUIRE(v_int[99] == 99);
  v_int.pop_back();
  REQUIRE(v_int.size() == 99);
  REQUIRE(v_int[98] == 98);

  zstd::vector<Foo> v_foo;
  for (int i = 0; i < 100; ++i) {
    v_foo.push_back(Foo(i, i / 2.0));
  }
  REQUIRE(v_foo.size() == 100);
  REQUIRE(v_foo[99] == Foo(99, 49.5));
  v_foo.pop_back();
  REQUIRE(v_foo.size() == 99);
  REQUIRE(v_foo[98] == Foo(98, 49.0));
}

void test_resize() {
  zstd::vector<int> v_int(100, 1);
  REQUIRE(v_int.size() == 100);
  v_int.resize(100);
  REQUIRE(v_int.size() == 100);
  for (int i = 0; i < v_int.size(); ++i) {
    REQUIRE(v_int[i] == 1);
  }
  v_int.resize(50);
  REQUIRE(v_int.size() == 50);
  for (int i = 0; i < v_int.size(); ++i) {
    REQUIRE(v_int[i] == 1);
  }
  v_int.resize(150);
  REQUIRE(v_int.size() == 150);
  for (int i = 0; i < 50; ++i) {
    REQUIRE(v_int[i] == 1);
  }
  for (int i = 50; i < v_int.size(); ++i) {
    REQUIRE(v_int[i] == int());
  }

  Foo foo(1, 0.5);
  zstd::vector<Foo> v_foo(100, foo);
  REQUIRE(v_foo.size() == 100);
  v_foo.resize(100);
  REQUIRE(v_foo.size() == 100);
  for (int i = 0; i < v_foo.size(); ++i) {
    REQUIRE(v_foo[i] == foo);
  }
  v_foo.resize(50);
  REQUIRE(v_foo.size() == 50);
  for (int i = 0; i < v_foo.size(); ++i) {
    REQUIRE(v_foo[i] == foo);
  }
  v_foo.resize(150);
  REQUIRE(v_foo.size() == 150);
  for (int i = 0; i < 50; ++i) {
    REQUIRE(v_foo[i] == foo);
  }
  for (int i = 50; i < v_foo.size(); ++i) {
    REQUIRE(v_foo[i] == Foo());
  }
}

void test_fill_resize() {
  zstd::vector<int> v_int(100, 1);
  REQUIRE(v_int.size() == 100);
  v_int.resize(100, 1);
  REQUIRE(v_int.size() == 100);
  for (int i = 0; i < v_int.size(); ++i) {
    REQUIRE(v_int[i] == 1);
  }
  v_int.resize(50, 3);
  REQUIRE(v_int.size() == 50);
  for (int i = 0; i < v_int.size(); ++i) {
    REQUIRE(v_int[i] == 1);
  }
  v_int.resize(150, 3);
  for (int i = 0; i < 50; ++i) {
    REQUIRE(v_int[i] == 1);
  }
  for (int i = 50; i < v_int.size(); ++i) {
    REQUIRE(v_int[i] == 3);
  }

  zstd::vector<Foo> v_foo(100, Foo(1, 0.5));
  REQUIRE(v_foo.size() == 100);
  v_foo.resize(100, Foo(3, 1.5));
  REQUIRE(v_foo.size() == 100);
  for (int i = 0; i < v_foo.size(); ++i) {
    REQUIRE(v_foo[i] == Foo(1, 0.5));
  }
  v_foo.resize(50, Foo(3, 1.5));
  REQUIRE(v_foo.size() == 50);
  for (int i = 0; i < v_foo.size(); ++i) {
    REQUIRE(v_foo[i] == Foo(1, 0.5));
  }
  v_foo.resize(150, Foo(3, 1.5));
  REQUIRE(v_foo.size() == 150);
  for (int i = 0; i < 50; ++i) {
    REQUIRE(v_foo[i] == Foo(1, 0.5));
  }
  for (int i = 50; i < v_foo.size(); ++i) {
    REQUIRE(v_foo[i] == Foo(3, 1.5));
  }
}

void test_swap() {
  zstd::vector<int> v_int_1(50, 1);
  zstd::vector<int> v_int_2(100, 3);
  REQUIRE(v_int_1.size() == 50);
  REQUIRE(v_int_2.size() == 100);
  for (int i = 0; i < v_int_1.size(); ++i) {
    REQUIRE(v_int_1[i] == 1);
  }
  for (int i = 0; i < v_int_2.size(); ++i) {
    REQUIRE(v_int_2[i] == 3);
  }
  v_int_1.swap(v_int_2);
  REQUIRE(v_int_1.size() == 100);
  REQUIRE(v_int_2.size() == 50);
  for (int i = 0; i < v_int_1.size(); ++i) {
    REQUIRE(v_int_1[i] == 3);
  }
  for (int i = 0; i < v_int_2.size(); ++i) {
    REQUIRE(v_int_2[i] == 1);
  }

  zstd::vector<Foo> v_foo_1(50, Foo(1, 0.5));
  zstd::vector<Foo> v_foo_2(100, Foo(3, 1.5));
  REQUIRE(v_foo_1.size() == 50);
  REQUIRE(v_foo_2.size() == 100);
  for (int i = 0; i < v_foo_1.size(); ++i) {
    REQUIRE(v_foo_1[i] == Foo(1, 0.5));
  }
  for (int i = 0; i < v_foo_2.size(); ++i) {
    REQUIRE(v_foo_2[i] == Foo(3, 1.5));
  }
  v_foo_1.swap(v_foo_2);
  REQUIRE(v_foo_1.size() == 100);
  REQUIRE(v_foo_2.size() == 50);
  for (int i = 0; i < v_foo_1.size(); ++i) {
    REQUIRE(v_foo_1[i] == Foo(3, 1.5));
  }
  for (int i = 0; i < v_foo_2.size(); ++i) {
    REQUIRE(v_foo_2[i] == Foo(1, 0.5));
  }
}


int main() {
  test_default_constructor();
  test_default_alloc_constructor();
  test_default_n_constructor();
  test_default_n_alloc_constructor();
  test_fill_n_constructor();
  test_fill_n_alloc_constructor();
  test_range_constructor();
  test_range_alloc_constructor();
  test_init_list_constructor();
  test_init_list_alloc_constructor();
  test_copy_constructor();
  test_copy_alloc_constructor();
  test_move_contructor();
  test_move_alloc_constructor();
  test_copy_assignment_operator();
  test_move_assignment_operator();
  test_init_list_assignment_operator();
  test_destructor();
  test_fill_n_assign();
  test_range_assign();
  test_init_list_assign();
  test_get_allocator();
  test_begin();
  test_const_begin();
  test_cbegin();
  test_end();
  test_const_end();
  test_cend();
  test_rbegin();
  test_const_rbegin();
  test_rend();
  test_const_rend();
  test_crend();
  test_empty();
  test_size();
  test_max_size();
  test_capacity();
  test_reserve();
  test_shrink_to_fit();
  test_index_access();
  test_const_index_access();
  test_at();
  test_const_at();
  test_front();
  test_const_front();
  test_back();
  test_const_back();
  test_data();
  test_const_data();
  test_clear();
  test_copy_insert();
  test_move_insert();
  test_insert_n();
  test_range_insert();
  test_emplace();
  test_erase();
  test_range_erase();
  test_copy_push_back();
  test_move_push_back();
  test_emplace_back();
  test_pop_back();
  test_resize();
  test_fill_resize();
  test_swap();
}