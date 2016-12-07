#ifndef ZSTD_INTERNAL_MEMORY_UNINITIALIZED_H_
#define ZSTD_INTERNAL_MEMORY_UNINITIALIZED_H_

#include "addressof.h"
#include "construct_destroy.h"
#include "allocator.h"
#include "allocator_traits.h"

#include "../algorithm/basic_sequence_modifier.h"
#include "../iterator/iterator_adaptor.h"
#include "../type_traits/type_property.h"
#include "../type_traits/class_property.h"
#include "../utility/move.h"


namespace zstd {

namespace internal {

template <bool IsTrivial>
struct Uninitialized {
  template <typename InputIterator, typename ForwardIterator>
  static ForwardIterator copy(InputIterator first, InputIterator last, 
                              ForwardIterator result) {
    ForwardIterator current = result;
    try {
      for (; first != last; ++first, ++current) {
        zstd::internal::construct(zstd::addressof(*current), *first);
      }
      return current;
    } catch (...) {
      zstd::internal::destroy(result, current);
      throw;
    }
  }
  template <typename ForwardIterator, typename Tp>
  static void fill(ForwardIterator first, ForwardIterator last, const Tp& value) {
    ForwardIterator current = first;
    try {
      for (; current != last; ++current) {
        zstd::internal::construct(zstd::addressof(*current), value);
      }
    } catch (...) {
      zstd::internal::destroy(first, current);
      throw;
    }
  }
  template <typename ForwardIterator, typename Size, typename Tp>
  static void fill_n(ForwardIterator first, Size n, const Tp& value) {
    ForwardIterator current = first;
    try {
      for (; n > 0; --n, ++current) {
        zstd::internal::construct(zstd::addressof(*current), value);
      }
    } catch (...) {
      zstd::internal::destroy(first, current);
      throw;
    }
  }
};

template <>
struct Uninitialized<true> {
  template <typename InputIterator, typename ForwardIterator>
  static ForwardIterator copy(InputIterator first, InputIterator last, 
                              ForwardIterator result) {
    return zstd::copy(first, last, result);
  }
  template <typename ForwardIterator, typename Tp>
  static void fill(ForwardIterator first, ForwardIterator last, const Tp& value) {
    zstd::fill(first, last, value);
  }
  template <typename ForwardIterator, typename Size, typename Tp>
  static void fill_n(ForwardIterator first, Size n, const Tp& value) {
    zstd::fill_n(first, n, value);
  }
};

}  // namespace internal


/* uninitialized_copy */
template <typename InputIterator, typename ForwardIterator>
inline ForwardIterator uninitialized_copy(InputIterator first, 
  InputIterator last, ForwardIterator result) {
  typedef typename zstd::iterator_traits<InputIterator>::value_type InputVal;
  typedef typename zstd::iterator_traits<ForwardIterator>::value_type 
          ForwardVal;
  typedef typename zstd::iterator_traits<InputIterator>::reference InputRef;
  typedef typename zstd::iterator_traits<ForwardIterator>::reference 
          ForwardRef;
  const bool trival = zstd::is_trivial<InputVal>::value &&
                      zstd::is_trivial<ForwardVal>::value &&
                      zstd::is_assignable<ForwardRef, InputRef>::value;
  return internal::Uninitialized<trival>::copy(first, last, result);
}

/* uninitialized_fill */
template <typename ForwardIterator, typename Tp>
inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, 
                               const Tp& value) {
  typedef typename zstd::iterator_traits<ForwardIterator>::value_type 
          ForwardVal;
  const bool trival = zstd::is_trivial<ForwardVal>::value &&
                      zstd::is_copy_assignable<ForwardVal>::value;
  internal::Uninitialized<trival>::fill(first, last, value);
}

/* uninitialized_fill_n */
template <typename ForwardIterator, typename Size, typename Tp>
inline void uninitialized_fill_n(ForwardIterator first, Size n, 
                                 const Tp& value) {
  typedef typename zstd::iterator_traits<ForwardIterator>::value_type 
          ForwardVal;
  const bool trival = zstd::is_trivial<ForwardVal>::value &&
                      zstd::is_copy_assignable<ForwardVal>::value;
  internal::Uninitialized<trival>::fill_n(first, n, value);
}


/* Allocator versions of uninitialized functions */
namespace internal {

/* uninitialized_copy_alloc */
template <typename InputIterator, typename ForwardIterator, typename Allocator>
ForwardIterator uninitialized_copy_alloc(InputIterator first, 
  InputIterator last, ForwardIterator result, Allocator& alloc) {
  ForwardIterator current = result;
  try {
    for (; first != last; ++first, ++current) {
      zstd::allocator_traits<Allocator>::construct(
        alloc, zstd::addressof(*current), *first);
    }
    return current;
  } catch (...) {
    zstd::internal::destroy(result, current, alloc);
    throw;
  }
}
template <typename InputIterator, typename ForwardIterator, typename Tp>
inline ForwardIterator uninitialized_copy_alloc(InputIterator first,
  InputIterator last, ForwardIterator result, zstd::allocator<Tp>&) {
  return zstd::uninitialized_copy(first, last, result);
}

/* uninitialized_fill_alloc */
template <typename ForwardIterator, typename Tp, typename Allocator>
void uninitialized_fill_alloc(ForwardIterator first, ForwardIterator last,
                              const Tp& value, Allocator& alloc) {
  ForwardIterator current = first;
  try {
    for (; current != last; ++current) {
      zstd::allocator_traits<Allocator>::construct(
        alloc, zstd::addressof(*current), value);
    }
  } catch (...) {
    zstd::internal::destroy(first, current, alloc);
    throw;
  }
}
template <typename ForwardIterator, typename Tp1, typename Tp2>
inline void uninitialized_fill_alloc(ForwardIterator first, 
  ForwardIterator last, const Tp1& value, zstd::allocator<Tp2>&) {
  zstd::uninitialized_fill(first, last, value);
}

/* uninitialized_fill_n_alloc */
template <typename ForwardIterator, typename Size, typename Tp, 
          typename Allocator>
void uninitialized_fill_n_alloc(ForwardIterator first, Size n, 
                                const Tp& value, Allocator& alloc) {
  ForwardIterator current = first;
  try {
    for (; n > 0; --n, ++current) {
      zstd::allocator_traits<Allocator>::construct(
        alloc, zstd::addressof(*current), value);
    }
  } catch (...) {
    zstd::internal::destroy(first, current, alloc);
    throw;
  }
}
template <typename ForwardIterator, typename Size, typename Tp1,
          typename Tp2>
inline void uninitialized_fill_n_alloc(ForwardIterator first, Size n,
  const Tp1& value, zstd::allocator<Tp2>&) {
  zstd::uninitialized_fill_n(first, n, value);
}

/* uninitialized_move_alloc */
template <typename InputIterator, typename ForwardIterator, 
          typename Allocator>
inline ForwardIterator uninitialized_move_alloc(InputIterator first,
  InputIterator last, ForwardIterator result, Allocator& alloc) {
  return uninitialized_copy_alloc(zstd::make_move_iterator(first),
    zstd::make_move_iterator(last), result, alloc);
}

template <typename InputIterator, typename ForwardIterator,
          typename Allocator>
inline ForwardIterator uninitialized_move_if_no_except_alloc(
  InputIterator first, InputIterator last, ForwardIterator result,
  Allocator& alloc) {
  return uninitialized_copy_alloc(
           make_move_if_noexcept_iterator(first),
           make_move_if_noexcept_iterator(last),
           result, alloc);
}
  
/* uninitialized_copy_move */
template <typename InputIterator1, typename InputIterator2, 
          typename ForwardIterator, typename Allocator>
inline ForwardIterator uninitialized_copy_move(InputIterator1 first1,
  InputIterator1 last1, InputIterator2 first2, InputIterator2 last2,
  ForwardIterator result, Allocator& alloc) {

  ForwardIterator mid = uninitialized_copy_alloc(first1, last1, result, alloc);
  try {
    return uninitialized_move_alloc(first2, last2, mid, alloc);
  } catch (...) {
    zstd::internal::destroy(result, mid, alloc);
    throw;
  }
}

/* uninitialized_move_copy */
template <typename InputIterator1, typename InputIterator2, 
          typename ForwardIterator, typename Allocator>
inline ForwardIterator uninitialized_move_copy(InputIterator1 first1,
  InputIterator1 last1, InputIterator2 first2, InputIterator2 last2,
  ForwardIterator result, Allocator& alloc) {

  ForwardIterator mid = uninitialized_move_alloc(
    first1, last1, result, alloc);
  try {
    return uninitialized_copy_alloc(first2, last2, mid, alloc);
  } catch (...) {
    zstd::internal::destroy(result, mid, alloc);
    throw;
  }
}

// uninitialized_fill_move
template <typename ForwardIterator, typename Tp, typename InputIterator,
          typename Allocator>
inline ForwardIterator uninitialized_fill_move(ForwardIterator result,
  ForwardIterator mid, const Tp& value, InputIterator first, 
  InputIterator last, Allocator& alloc) {

  uninitialized_fill_alloc(result, mid, value, alloc);
  try {
    return uninitialized_move_alloc(first, last, mid, alloc);
  } catch (...) {
    zstd::internal::destroy(result, mid, alloc);
    throw;
  }
}

// uninitialized_move_fill
template <typename InputIterator, typename ForwardIterator, typename Tp,
          typename Allocator>
inline void uninitialized_move_fill(InputIterator first1, InputIterator last1,
  ForwardIterator first2, ForwardIterator last2, const Tp& value,
  Allocator& alloc) {

  ForwardIterator mid2 = uninitialized_move_alloc(
    first1, last1, first2, alloc);
  try {
    uninitialized_fill_alloc(mid2, last2, value, alloc);
  } catch (...) {
    zstd::internal::destroy(first2, mid2, alloc);
    throw;
  }
}

}  // namespace internal

}  // namespace zstd

#endif  // ZSTD_INTERNAL_MEMORY_UNINITIALIZED_H_
