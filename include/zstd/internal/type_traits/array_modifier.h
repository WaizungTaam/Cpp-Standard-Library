#ifndef ZSTD_INTERNAL_TYPE_TRAITS_ARRAY_MODIFIER_H_
#define ZSTD_INTERNAL_TYPE_TRAITS_ARRAY_MODIFIER_H_

#include "../cstddef/cstddef.h"

namespace zstd {

/* remove_extent */
template <typename Tp>
struct remove_extent {
	typedef Tp type;
};

template <typename Tp, zstd::size_t Size>
struct remove_extent<Tp[Size]> {
	typedef Tp type;
};

template <typename Tp>
struct remove_extent<Tp[]> {
	typedef Tp type;
};


/* remove_all_extents */
template <typename Tp>
struct remove_all_extents {
	typedef Tp type;
};

template <typename Tp, zstd::size_t Size>
struct remove_all_extents<Tp[Size]> {
	typedef typename remove_all_extents<Tp>::type type;
};

template <typename Tp>
struct remove_all_extents<Tp[]> {
	typedef typename remove_all_extents<Tp>::type type;
};


template <typename Tp>
using remove_extent_t = typename remove_extent<Tp>::type;

template <typename Tp>
using remove_all_extents_t = typename remove_all_extents<Tp>::type;


}  // namespace zstd

#endif  // ZSTD_INTERNAL_TYPE_TRAITS_ARRAY_MODIFIER_H_