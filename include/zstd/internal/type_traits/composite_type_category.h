#ifndef ZSTD_INTERNAL_TYPE_TRAITS_COMPOSITE_TYPE_CATEGORY_H_
#define ZSTD_INTERNAL_TYPE_TRAITS_COMPOSITE_TYPE_CATEGORY_H_

#include "type_traits_base.h"
#include "cv_modifier.h"
#include "type_traits_logic.h"
#include "primary_type_category.h"

namespace zstd {

/* is_arithmetic */
template <typename Tp>
struct is_arithmetic : 
  public internal::or_t<is_integral<Tp>, is_floating_point<Tp>>::type {};

/* is_reference */
template <typename Tp>
struct is_reference : 
	public internal::or_t<is_lvalue_reference<Tp>, 
											 is_rvalue_reference<Tp>>::type {};

/* is_fundamental */
template <typename Tp>
struct is_fundamental :
	public internal::or_t<is_arithmetic<Tp>, is_void<Tp>, 
											 is_null_pointer<Tp>>::type {};

/* is_object */
template <typename Tp>
struct is_object :
  public internal::not_t<internal::or_t<is_function<Tp>, is_reference<Tp>,
  																	    is_void<Tp>>>::type {};

/* is_compound */
template <typename Tp>
struct is_compound :
	public integral_constant<bool, !is_fundamental<Tp>::value> {};

/* is_member_pointer */
namespace internal {
template <typename Tp>
struct is_member_pointer : public zstd::false_type {};
template <typename Tp, typename Class>
struct is_member_pointer<Tp Class::*> : public zstd::true_type {};
}  // namespace internal
template <typename Tp>
struct is_member_pointer :
	public internal::is_member_pointer<typename remove_cv<Tp>::type>::type {};

/* is_scalar */
template <typename Tp>
struct is_scalar :
	public internal::or_t<is_arithmetic<Tp>, is_enum<Tp>, is_pointer<Tp>,
											is_member_pointer<Tp>, is_null_pointer<Tp>>::type {};

namespace internal {

/* is_referenceable */
template <typename Tp>
struct is_referenceable : public or_t<zstd::is_object<Tp>, 
																		zstd::is_reference<Tp>>::type {};

template <typename Ret, typename... Args>
struct is_referenceable<Ret(Args...)> : public zstd::true_type {};

template <typename Ret, typename... Args>
struct is_referenceable<Ret(Args......)> : public zstd::true_type {};

}  // namespace internal

}  // namespace zstd

#endif  // ZSTD_INTERNAL_TYPE_TRAITS_COMPOSITE_TYPE_CATEGORY_H_
