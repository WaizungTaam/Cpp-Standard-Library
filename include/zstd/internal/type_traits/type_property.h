#ifndef ZSTD_INTERNAL_TYPE_TRAITS_TYPE_PROPERTY_H_
#define ZSTD_INTERNAL_TYPE_TRAITS_TYPE_PROPERTY_H_

#include "type_traits_base.h"
#include "type_traits_logic.h"
#include "composite_type_category.h"

namespace zstd {

/* is_const */
template <typename>
struct is_const : public false_type {};

template <typename Tp>
struct is_const<const Tp> : public true_type {};


/* is_volatile */
template <typename>
struct is_volatile : public false_type {};

template <typename Tp>
struct is_volatile<volatile Tp> : public true_type {};


/* is_trivial */
// __is_trivial is a gcc function.
template <typename Tp>
struct is_trivial : public integral_constant<bool, __is_trivial(Tp)> {};


/* is_trivially_copyable */


/* is_standard_layout */
// __is_standard_layout is a gcc function.
template <typename Tp>
struct is_standard_layout :
	public integral_constant<bool, __is_standard_layout(Tp)> {};


/* is_pod */
// __is_pod is a gcc function.
template <typename Tp>
struct is_pod :
	public integral_constant<bool, __is_pod(Tp)> {};


/* is_literal_type */
template <typename Tp>
struct is_literal_type :
	public integral_constant<bool, __is_literal_type(Tp)> {};


/* is_empty */
template <typename Tp>
struct is_empty :
	public integral_constant<bool, __is_empty(Tp)> {};


/* is_polymorphic */
template <typename Tp>
struct is_polymorphic :
	public integral_constant<bool, __is_polymorphic(Tp)> {};


/* is_final */
template <typename Tp>
struct is_final :
	public integral_constant<bool, __is_final(Tp)> {};


/* is_abstract */
template <typename Tp>
struct is_abstract :
	public integral_constant<bool, __is_abstract(Tp)> {};


/* is_signed */
namespace internal {
template <typename Tp, bool = zstd::is_arithmetic<Tp>::value>
struct is_signed : public zstd::false_type {};
template <typename Tp>
struct is_signed<Tp, true> : 
	public integral_constant<bool, Tp(-1) < Tp(0)> {};
}  // namespace internal
template <typename Tp>
struct is_signed : public internal::is_signed<Tp>::type {};


/* is_unsigned */
template <typename Tp>
struct is_unsigned :
	public internal::and_t<is_arithmetic<Tp>, 
											   internal::not_t<is_signed<Tp>>>::type {};

}  // namespace zstd

#endif  // ZSTD_INTERNAL_TYPE_TRAITS_TYPE_PROPERTY_H_
