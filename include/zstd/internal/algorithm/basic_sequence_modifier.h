#ifndef ZSTD_INTERNAL_ALGORITHM_BASIC_SEQUENCE_MODIFIER_H_
#define ZSTD_INTERNAL_ALGORITHM_BASIC_SEQUENCE_MODIFIER_H_

#include "../iterator/iterator_base.h"
#include "../iterator/iterator_traits.h"
#include "../utility/move.h"

#include <string.h>

namespace zstd {

/* copy */
namespace internal {
template <typename InputIt, typename OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt result, 
              zstd::input_iterator_tag) {
  for (; first != last; ++first, ++result) {
    *result = *first;
  }
  return result;
}
template <typename RandomAccessIt, typename OutputIt>
OutputIt copy(RandomAccessIt first, RandomAccessIt last, OutputIt result,
              zstd::random_access_iterator_tag) {
  typedef typename zstd::iterator_traits<RandomAccessIt>::difference_type 
  			  Distance;
  for (Distance n = last - first; n > 0; --n) {
    *result = *first;
    ++first;
    ++result;
  }
  return result;
}
template <typename Tp>
Tp* copy_trivial(const Tp* first, const Tp* last, Tp* result) {
  memmove(result, first, sizeof(Tp) * (last - first));
  return result + (last - first);
}
}  // namespace internal
template <typename InputIt, typename OutputIt>
inline OutputIt copy(InputIt first, InputIt last, OutputIt result) {
  return internal::copy(first, last, result, 
         typename zstd::iterator_traits<InputIt>::iterator_category());
}
inline char* copy(const char* first, const char* last, char* result) 
{ internal::copy_trivial(first, last, result); }
inline signed char* copy(const signed char* first, const signed char* last,
                         signed char* result) 
{ return internal::copy_trivial(first, last, result); }
inline unsigned char* copy(const unsigned char* first, 
  const unsigned char* last, unsigned char* result) 
{ return internal::copy_trivial(first, last, result); }
inline short* copy(const short* first, const short* last, short* result) 
{ return internal::copy_trivial(first, last, result); }
inline unsigned short* copy(const unsigned short* first, 
  const unsigned short* last, unsigned short* result) 
{ return internal::copy_trivial(first, last, result); }
inline int* copy(const int* first, const int* last, int* result) 
{ return internal::copy_trivial(first, last, result); }
inline unsigned int* copy(const unsigned int* first, const unsigned int* last,
                          unsigned int* result) 
{ return internal::copy_trivial(first, last, result); }
inline long* copy(const long* first, const long* last, long* result) 
{ return internal::copy_trivial(first, last, result); }
inline unsigned long* copy(const unsigned long* first, 
  const unsigned long* last, unsigned long* result) 
{ return internal::copy_trivial(first, last, result); }
inline long long* copy(const long long* first, const long long* last,
                       long long* result) 
{ return internal::copy_trivial(first, last, result); }
inline unsigned long long* copy(const unsigned long long* first,
  const unsigned long long* last, unsigned long long* result)
{ return internal::copy_trivial(first, last, result); }
inline wchar_t* copy(const wchar_t* first, const wchar_t* last,
                     wchar_t* result)
{ return internal::copy_trivial(first, last, result); }
inline float* copy(const float* first, const float* last, float* result)
{ return internal::copy_trivial(first, last, result); }
inline double* copy(const double* first, const double* last, double* result)
{ return internal::copy_trivial(first, last, result); }
inline long double* copy(const long double* first, const long double* last,
                         long double* result)
{ return internal::copy_trivial(first, last, result); }

/* copy_if */
namespace internal {
template <typename InputIt, typename OutputIt, typename UnaryPredicate>
OutputIt copy_if(InputIt first, InputIt last, OutputIt result,
                 UnaryPredicate pred) {
  for (; first != last; ++first) {
    if (pred(*first)) {
      *result = *first;
      ++result;
    }
  }
  return result;
}
}  // namespace internal
template <typename InputIt, typename OutputIt, typename UnaryPredicate>
inline OutputIt copy_if(InputIt first, InputIt last, OutputIt result,
                        UnaryPredicate pred) {
  return internal::copy_if(first, last, result, pred);
}

/* copy_n */
namespace internal {
template <typename InputIt, typename Size, typename OutputIt>
OutputIt copy_n(InputIt first, Size n, OutputIt result, 
								zstd::input_iterator_tag) {
  if (n <= 0) return result;
  for (;;) {
    *result = *first;
    ++result;
    --n;
    if (n > 0) ++first;
    else break;
  }
  return result;
}
template <typename RandomAccessIt, typename Size, typename OutputIt>
OutputIt copy_n(RandomAccessIt first, Size n, OutputIt result, 
                zstd::random_access_iterator_tag) {
  return zstd::copy(first, first + n, result);
}
}  // namespace internal
template <typename InputIt, typename Size, typename OutputIt>
inline OutputIt copy_n(InputIt first, Size n, OutputIt result) {
  return internal::copy_n(first, n, result, 
         typename zstd::iterator_traits<InputIt>::iterator_category());
}

/* copy_backward */
namespace internal {
template <typename BidirectionalIt1, typename BidirectionalIt2, 
          typename Distance>
BidirectionalIt2 copy_backward(BidirectionalIt1 first, BidirectionalIt1 last,
  BidirectionalIt2 result, zstd::bidirectional_iterator_tag) {
  while (first != last) {
    --result; --last;
    *result = *last;
  }
  return result;
}
template <typename RandomAccessIt, typename BidirectionalIt, 
          typename Distance>
BidirectionalIt copy_backward(RandomAccessIt first, RandomAccessIt last,
  BidirectionalIt result, zstd::random_access_iterator_tag) {
  for (Distance n = last - first; n > 0; --n) {
    --result; --last;
    *result = *last;
  }
  return result;
}
}  // namespace internal
template <typename BidirectionalIt1, typename BidirectionalIt2>
inline BidirectionalIt2 copy_backward(BidirectionalIt1 first, 
  BidirectionalIt1 last, BidirectionalIt2 result) {
  return internal::copy_backward(first, last, result, 
         typename zstd::iterator_traits<
         BidirectionalIt1>::iterator_category());
}

/* move */
namespace internal {
template <typename InputIt, typename OutputIt>
OutputIt move(InputIt first, InputIt last, OutputIt result, 
              zstd::input_iterator_tag) {
  for (; first != last; ++first, ++result) {
    *result = zstd::move(*first);
  }
  return result;
}
template <typename RandomAccessIt, typename OutputIt>
OutputIt move(RandomAccessIt first, RandomAccessIt last, OutputIt result,
              zstd::random_access_iterator_tag) {
  typedef typename iterator_traits<RandomAccessIt>::difference_type Distance;
  for (Distance n = last - first; n > 0; --n) {
    *result = zstd::move(*first);
    ++first;
    ++result;
  }
  return result;
}
}  // namespace internal
template <typename InputIt, typename OutputIt>
inline OutputIt move(InputIt first, InputIt last, OutputIt result) {
  return internal::move(first, last, result, 
         typename zstd::iterator_traits<InputIt>::iterator_category());
}

/* move_backward */
namespace internal {
template <typename BidirectionalIt1, typename BidirectionalIt2>
BidirectionalIt2 move_backward(BidirectionalIt1 first, BidirectionalIt1 last,
  BidirectionalIt2 result, zstd::bidirectional_iterator_tag) {
  while (first != last) {
    --result; --last;
    *result = zstd::move(*last);
  }
  return result;
}
template <typename RandomAccessIt, typename BidirectionalIt>
BidirectionalIt move_backward(RandomAccessIt first, RandomAccessIt last,
  BidirectionalIt result, zstd::random_access_iterator_tag) {
  typedef typename iterator_traits<RandomAccessIt>::difference_type Distance;
  for (Distance n = last - first; n > 0; --n) {
    --result; --last;
    *result = zstd::move(*last);
  }
  return result;
}
}  // namespace internal
template <typename BidirectionalIt1, typename BidirectionalIt2>
inline BidirectionalIt2 move_backward(BidirectionalIt1 first, 
  BidirectionalIt1 last, BidirectionalIt2 result) {
  return internal::move_backward(first, last, result, 
         typename zstd::iterator_traits<
         BidirectionalIt1>::iterator_category());
}

/* fill */
namespace internal {
template <typename ForwardIt, typename Value>
void fill(ForwardIt first, ForwardIt last, const Value& value) {
  for (; first != last; ++first) {
    *first = value;
  }
}
}  // namespace internal
template <typename ForwardIt, typename Value>
inline void fill(ForwardIt first, ForwardIt last, const Value& value) {
  internal::fill(first, last, value);
}
inline void fill(unsigned char* first, unsigned char* last, 
                 const unsigned char& value) {
  unsigned char value_copy = value;
  memset(first, value_copy, last - first);
}
inline void fill(signed char* first, signed char* last, 
                  const signed char& value) {
  signed char value_copy = value;
  memset(first, static_cast<unsigned char>(value_copy), last - first);
}
inline void fill(char* first, char* last, const char& value) {
  char value_copy = value;
  memset(first, static_cast<unsigned char>(value_copy), last - first);
}

/* fill_n */
namespace internal {
template <typename OutputIt, typename Size, typename Value>
OutputIt fill_n(OutputIt first, Size n, const Value& value) {
  for (; n > 0; --n, ++first) {
    *first = value;
  }
  return first;
}
}  // namespace internal
template <typename OutputIt, typename Size, typename Value>
inline OutputIt fill_n(OutputIt first, Size n, const Value& value) {
  return internal::fill_n(first, n, value);
}
template <typename Size>
inline unsigned char* fill_n(unsigned char* first, Size n, 
                             const unsigned char& value) {
  fill(first, first + n, value);
  return first + n;
}
template <typename Size>
inline signed char* fill_n(signed char* first, Size n, 
                           const signed char& value) {
  fill(first, first + n, value);
  return first + n;
}
template <typename Size>
inline char* fill_n(char* first, Size n, const char& value) {
  fill(first, first + n, value);
  return first + n;
}

}  // namespace zstd

#endif  // ZSTD_INTERNAL_ALGORITHM_BASIC_SEQUENCE_MODIFIER_H_