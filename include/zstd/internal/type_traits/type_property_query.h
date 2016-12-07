#ifndef ZSTD_INTERNAL_TYPE_TRAITS_TYPE_PROPERTY_QUERY_H_
#define ZSTD_INTERNAL_TYPE_TRAITS_TYPE_PROPERTY_QUERY_H_

#include "type_traits_base.h"

#include "../cstddef/cstddef.h"

namespace zstd {

/* alignment_of */
template <typename Tp>
struct alignment_of : 
	public integral_constant<zstd::size_t, __alignof__(Tp)> {};


/* rank */
template <typename>
struct rank : public integral_constant<zstd::size_t, 0> {};

template <typename Tp, zstd::size_t Size>
struct rank<Tp[Size]> : 
	public integral_constant<zstd::size_t, rank<Tp>::value + 1> {};

template <typename Tp>
struct rank<Tp[]> : 
	public integral_constant<zstd::size_t, rank<Tp>::value + 1> {};


/* extent */
template <typename, unsigned>
struct extent : public integral_constant<zstd::size_t, 0> {};

template <typename Tp, unsigned Uint, zstd::size_t Size>
struct extent<Tp[Size], Uint> :
	public integral_constant<zstd::size_t, 
	Uint == 0 ? Size : extent<Tp, Uint - 1>::value> {};

template <typename Tp, unsigned Uint>
struct extent<Tp[], Uint> :
	public integral_constant<zstd::size_t,
	Uint == 0 ? 0 : extent<Tp, Uint - 1>::value> {};

}  // namespace zstd

#endif  // ZSTD_INTERNAL_TYPE_TRAITS_TYPE_PROPERTY_QUERY_H_