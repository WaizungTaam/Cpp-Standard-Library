#ifndef ZSTD_INTERNAL_ITERATOR_ITERATOR_TRAITS_H_
#define ZSTD_INTERNAL_ITERATOR_ITERATOR_TRAITS_H_

#include "iterator_base.h"

#include "../cstddef/cstddef.h"
#include "../type_traits/type_traits_base.h"
#include "../type_traits/cv_modifier.h"


namespace zstd {

namespace internal {

template <typename Tp>
struct has_iterator_category_helper {
private:
  template <typename Up>
  struct wrap_type {};

  template <typename Up>
  static zstd::true_type test(wrap_type<typename Up::iterator_category>*);

  template <typename Up>
  static zstd::false_type test(...);

public:
  typedef decltype(test<Tp>(0)) type;
};

template <typename Tp>
struct has_iterator_category :
  public has_iterator_category_helper<
  typename zstd::remove_cv<Tp>::type>::type {};


template <typename Iterator,
          bool = has_iterator_category<Iterator>::value>
struct iterator_traits_impl {};

template <typename Iterator>
struct iterator_traits_impl<Iterator, true> {
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
};

}  // namespace internal


template <typename Iterator>
struct iterator_traits :
  public internal::iterator_traits_impl<Iterator> {};

template <typename Tp>
struct iterator_traits<Tp*> {
  typedef random_access_iterator_tag iterator_category;
  typedef Tp value_type;
  typedef zstd::ptrdiff_t difference_type;
  typedef Tp* pointer;
  typedef Tp& reference;
};

template <typename Tp>
struct iterator_traits<const Tp*> {
  typedef random_access_iterator_tag iterator_category;
  typedef Tp value_type;
  typedef zstd::ptrdiff_t difference_type;
  typedef const Tp* pointer;
  typedef const Tp& reference;
};

}  // namespace zstd

#endif  // ZSTD_INTERNAL_ITERATOR_ITERATOR_TRAITS_H_
