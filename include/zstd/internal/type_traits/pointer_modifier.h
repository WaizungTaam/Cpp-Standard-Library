#ifndef ZSTD_INTERNAL_TYPE_TRAITS_POINTER_MODIFIER_H_
#define ZSTD_INTERNAL_TYPE_TRAITS_POINTER_MODIFIER_H_

#include "type_traits_base.h"
#include "cv_modifier.h"
#include "type_traits_logic.h"

namespace zstd {

/* remove_pointer */
namespace internal {

template <typename Tp, typename>
struct remove_pointer { typedef Tp type; };
template <typename Tp1, typename Tp2>
struct remove_pointer<Tp1, Tp2*> { typedef Tp2 type; };

}  // namespace internal

template <typename Tp>
struct remove_pointer :
	public internal::remove_pointer<Tp, remove_cv<Tp>::type> {};


/* add_pointer */
namespace internal {

template <typename Tp, 
					bool = or_t<is_referenceable<Tp>, zstd::is_void<Tp>>::value>
struct add_pointer { typedef Tp type; };

template <typename Tp>
struct add_pointer<Tp, true> {
	typedef typename zstd::remove_reference<Tp>::type* type;
};

}  // namespace internal

template <typename Tp>
struct add_pointer : public internal::add_pointer<Tp> {};


template <typename Tp>
using remove_pointer_t = typename remove_pointer<Tp>::type;

template <typename Tp>
using add_pointer_t = typename add_pointer<Tp>::type;

}  // namespace zstd

#endif  // ZSTD_INTERNAL_TYPE_TRAITS_POINTER_MODIFIER_H_