#ifndef ZSTD_INTERNAL_MEMORY_CONSTRUCT_DESTROY_H_
#define ZSTD_INTERNAL_MEMORY_CONSTRUCT_DESTROY_H_

#include "addressof.h"
// #include "allocator_traits.h"

#include "../utility/forward.h"
#include "../iterator/iterator_traits.h"

#include <new>  // TODO

namespace zstd {
namespace internal {

/* construct */
template <typename Tp, typename... Args>
inline void construct(Tp* p, Args&&... args) {
  ::new(static_cast<void*>(p)) Tp(zstd::forward<Args>(args)...);
}


/* destroy */
template <typename Tp>
inline void destroy(Tp* p) { p->~Tp(); }

template <bool Is_trivially_destructible>
struct Destroy {
  template <typename ForwardIterator>
  static void destroy(ForwardIterator first, ForwardIterator last) {
    for (; first != last; ++first) {
      zstd::internal::destroy(zstd::addressof(*first));
    }
  }
};
template <>
struct Destroy<true> {
  template <typename ForwardIterator>
  static void destroy(ForwardIterator, ForwardIterator) {}
};

template <typename ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last) {
  typedef typename zstd::iterator_traits<ForwardIterator>::value_type Value;
  Destroy<__has_trivial_destructor(Value)>::destroy(first, last);
}

// template <typename ForwardIterator, typename Allocator>
// void destroy(ForwardIterator first, ForwardIterator last, Allocator& alloc) {
//   for (; first != last; ++first) {
//     typename zstd::allocator_traits<Allocator>::destroy(
//       alloc, zstd::addressof(*first));
//   }
// }

// template <typename ForwardIterator, typename Tp>
// inline void destroy(ForwardIterator first, ForwardIterator last, 
//                     zstd::allocator<Tp>&) {
//   zstd::internal::destroy(first, last);
// }

}  // namespace internal
}  // namespace zstd

#endif  // ZSTD_INTERNAL_MEMORY_CONSTRUCT_DESTROY_H_
