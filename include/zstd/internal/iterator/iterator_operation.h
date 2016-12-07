#ifndef ZSTD_INTERNAL_ITERATOR_ITERATOR_OPEREATION_H_
#define ZSTD_INTERNAL_ITERATOR_ITERATOR_OPEREATION_H_

#include "iterator_base.h"
#include "iterator_traits.h"

namespace zstd {

/* distance */
namespace internal {
template <typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last, zstd::input_iterator_tag) {
  typename zstd::iterator_traits<InputIterator>::difference_type result = 0;
  while (first != last) {
    ++first;
    ++result;
  }
  return result;
}
template <typename RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type
distance(RandomAccessIterator first, RandomAccessIterator last,
         zstd::random_access_iterator_tag) {
  return last - first;
}
}  // namespace internal

template <typename InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last) {
  return internal::distance(first, last, 
         typename iterator_traits<InputIterator>::iterator_category());
}


/* advance */
namespace internal {
template <typename InputIterator, typename Distance>
inline void advance(InputIterator& iterator, Distance distance, 
                    zstd::input_iterator_tag) {
  while (distance--) {
    ++iterator;
  }
}
template <typename BidirectionalIterator, typename Distance>
inline void advance(BidirectionalIterator& iterator, Distance distance, 
                    zstd::bidirectional_iterator_tag) {
  if (distance >= 0) {
    while (distance--) {
      ++iterator;
    }
  } else {
    while (distance++) {
      --iterator;
    }
  }
}
template <typename RandomAccessIterator, typename Distance>
inline void advance(RandomAccessIterator& iterator, Distance distance, 
                    zstd::random_access_iterator_tag) {
  iterator += distance;
}
}  // namespace internal

template <typename InputIterator, typename Distance>
inline void advance(InputIterator& iterator, Distance distance) {
  internal::advance(iterator, distance, 
    typename iterator_traits<InputIterator>::iterator_category());
}


/* next */
template <typename ForwardIterator>
ForwardIterator next(ForwardIterator it, 
  typename iterator_traits<ForwardIterator>::difference_type n = 1) {
  advance(it, n);
  return it;
}

/* prev */
template <typename BidirectionalIterator>
BidirectionalIterator prev(BidirectionalIterator it,
  typename iterator_traits<BidirectionalIterator>::difference_type n) {
  advance(it, -n);
  return it;
}

}  // namespace zstd

#endif  // ZSTD_INTERNAL_ITERATOR_ITERATOR_OPEREATION_H_
