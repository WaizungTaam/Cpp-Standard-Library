#ifndef ZSTD_INTERNAL_ITERATOR_ITERATOR_TRAITS_H_
#define ZSTD_INTERNAL_ITERATOR_ITERATOR_TRAITS_H_

#include "iterator_base.h"

#include "../cstddef/cstddef.h"

namespace zstd {

template <typename Iterator>
struct iterator_traits {
  typedef typename Iterator::iterator_category iterator_category;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
};

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