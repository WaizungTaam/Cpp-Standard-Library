#ifndef ZSTD_INTERNAL_ITERATOR_ITERATOR_BASE_H_
#define ZSTD_INTERNAL_ITERATOR_ITERATOR_BASE_H_

#include "../cstddef/cstddef.h"

namespace zstd {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template <typename Tp, typename Distance>
struct input_iterator {
  typedef input_iterator_tag iterator_category;
  typedef Tp value_type;
  typedef Distance difference_type;
  typedef Tp* pointer;
  typedef Tp& reference;
};
struct output_iterator {
  typedef output_iterator_tag iterator_category;
  typedef void value_type;
  typedef void difference_type;
  typedef void pointer;
  typedef void reference;
};
template <typename Tp, typename Distance>
struct forward_iterator {
  typedef forward_iterator_tag iterator_category;
  typedef Tp value_type;
  typedef Distance difference_type;
  typedef Tp* pointer;
  typedef Tp& reference;
};
template <typename Tp, typename Distance>
struct bidirectional_iterator {
  typedef bidirectional_iterator_tag iterator_category;
  typedef Tp value_type;
  typedef Distance difference_type;
  typedef Tp* pointer;
  typedef Tp& reference;
};
template <typename Tp, typename Distance>
struct random_access_iterator {
  typedef random_access_iterator_tag iterator_category;
  typedef Tp value_type;
  typedef Distance difference_type;
  typedef Tp* pointer;
  typedef Tp& reference;
};

template <typename Category, typename Tp, typename Distance = zstd::ptrdiff_t,
          typename Pointer = Tp*, typename Reference = Tp&>
struct iterator {
  typedef Category iterator_category;
  typedef Tp value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
};

}  // namespace zstd

#endif  // ZSTD_INTERNAL_ITERATOR_ITERATOR_BASE_H_