#ifndef ZSTD_INTERNAL_TYPE_TRAITS_TYPE_TRAITS_LOGIC_H_
#define ZSTD_INTERNAL_TYPE_TRAITS_TYPE_TRAITS_LOGIC_H_

#include "type_traits_base.h"
#include "conditional_type.h"

namespace zstd {
namespace internal {

/* or_t */
template <typename...>
struct or_t;

template <>
struct or_t<> : public zstd::false_type {};

template <typename T1>
struct or_t<T1> : public T1 {};

template <typename T1, typename T2>
struct or_t<T1, T2> : public zstd::conditional<T1::value, T1, T2>::type {};

template <typename T1, typename T2, typename T3, typename... Tn>
struct or_t<T1, T2, T3, Tn...> : 
  public zstd::conditional<T1::value, T1, or_t<T2, T3, Tn...>>::type {};


/* and */
template <typename...>
struct and_t;

template <>
struct and_t<> : public zstd::true_type {};

template <typename T1>
struct and_t<T1> : public T1 {};

template <typename T1, typename T2>
struct and_t<T1, T2> : public zstd::conditional<T1::value, T2, T1>::type {};

template <typename T1, typename T2, typename T3, typename... Tn>
struct and_t<T1, T2, T3, Tn...> :
  public zstd::conditional<T1::value, and_t<T2, T3, Tn...>, T1>::type {};


/* not */
template <typename T>
struct not_t : public zstd::integral_constant<bool, !T::value> {};

}  // namespace internal
}  // namespace zstd

#endif  // ZSTD_INTERNAL_TYPE_TRAITS_TYPE_TRAITS_LOGIC_H_