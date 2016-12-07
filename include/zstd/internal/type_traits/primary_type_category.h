#ifndef ZSTD_INTERNAL_TYPE_TRAITS_PRIMARY_TYPE_CATEGORY_H_
#define ZSTD_INTERNAL_TYPE_TRAITS_PRIMARY_TYPE_CATEGORY_H_

#include "type_traits_base.h"
#include "cv_modifier.h"

#include "../cstddef/cstddef.h"

namespace zstd {

/* is_void */
namespace internal {
template <typename> struct is_void : public zstd::false_type {};
template <> struct is_void<void> : public zstd::true_type {};
}  // namespace internal
template <typename Tp>
struct is_void : 
  public internal::is_void<typename remove_cv<Tp>::type>::type {};

/* is_null_pointer */
namespace internal {
template <typename> struct is_null_pointer : public zstd::false_type {};
template <> struct is_null_pointer<zstd::nullptr_t> : 
  public zstd::true_type {};
}  // namespace internal
template <typename Tp>
struct is_null_pointer :
  public internal::is_null_pointer<typename remove_cv<Tp>::type>::type {};

/* is_integral */
namespace internal {
template <typename> struct is_integral : public zstd::false_type {};
template <> struct is_integral<bool> : public zstd::true_type {};
template <> struct is_integral<char> : public zstd::true_type {};
template <> struct is_integral<signed char> : public zstd::true_type {};
template <> struct is_integral<unsigned char> : public zstd::true_type {};
template <> struct is_integral<wchar_t> : public zstd::true_type {};
template <> struct is_integral<char16_t> : public zstd::true_type {};
template <> struct is_integral<char32_t> : public zstd::true_type {};
template <> struct is_integral<short> : public zstd::true_type {};
template <> struct is_integral<unsigned short> : public zstd::true_type {};
template <> struct is_integral<int> : public zstd::true_type {};
template <> struct is_integral<unsigned int> : public zstd::true_type {};
template <> struct is_integral<long> : public zstd::true_type {};
template <> struct is_integral<unsigned long> : public zstd::true_type {};
template <> struct is_integral<long long> : public zstd::true_type {};
template <> struct is_integral<unsigned long long> : public zstd::true_type {};
}  // namespace internal
template <typename Tp>
struct is_integral : 
  public internal::is_integral<typename remove_cv<Tp>::type>::type {};

/* is_floating_point */
namespace internal {
template <typename> struct is_floating_point : public zstd::false_type {};
template <> struct is_floating_point<float> : public zstd::true_type {};
template <> struct is_floating_point<double> : public zstd::true_type {};
template <> struct is_floating_point<long double> : public zstd::true_type {};
}  // namespace internal
template <typename Tp>
struct is_floating_point :
  public internal::is_floating_point<typename remove_cv<Tp>::type>::type {};  

/* is_array */
template <typename> 
struct is_array : public false_type {};
template <typename Tp, zstd::size_t Size>
struct is_array<Tp[Size]> : public true_type {};
template <typename Tp> 
struct is_array<Tp[]> : public true_type {};

/* is_enum */
// __is_enum is a gcc function.
template <typename Tp>
struct is_enum : public integral_constant<bool, __is_enum(Tp)> {};

/* is_union */
template <typename Tp>
struct is_union : public integral_constant<bool, __is_union(Tp)> {};

/* is_class */
template <typename Tp>
struct is_class : public integral_constant<bool, __is_class(Tp)> {};

/* is_function */
template <typename> struct is_function : public false_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args...)> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args...)&> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args...)&&> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args......)> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args......)&> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args......)&&> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args...) const> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args...) const&> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args...) const&&> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args......) const> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args......) const&> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args......) const&&> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args...) volatile> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args...) volatile&> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args...) volatile&&> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args......) volatile> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args......) volatile&> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args......) volatile&&> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args...) const volatile> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args...) const volatile&> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args...) const volatile&&> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args......) const volatile> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args......) const volatile&> : public true_type {};
template <typename Ret, typename... Args>
struct is_function<Ret(Args......) const volatile&&> : public true_type {};

/* is_pointer */
namespace internal {
template <typename> struct is_pointer : public zstd::false_type {};
template <typename Tp> struct is_pointer<Tp*> : public zstd::true_type {};
}  // namespace internal
template <typename Tp>
struct is_pointer :
  public internal::is_pointer<typename remove_cv<Tp>::type>::type {};

/* is_lvalue_reference */
template <typename>
struct is_lvalue_reference : public false_type {};
template <typename Tp>
struct is_lvalue_reference<Tp&> : public true_type {};

/* is_rvalue_reference */
template <typename>
struct is_rvalue_reference : public false_type {};
template <typename Tp>
struct is_rvalue_reference<Tp&&> : public true_type {};

/* is_member_object_pointer */
namespace internal {
template <typename>
struct is_member_object_pointer : public zstd::false_type {};
template <typename Tp, typename Class>
struct is_member_object_pointer<Tp Class::*> :
  public integral_constant<bool, !zstd::is_function<Tp>::value> {};
// If a class member is not a member function, then it is a member object.
}  // namespace internal
template <typename Tp>
struct is_member_object_pointer :
  public internal::is_member_object_pointer<
  typename remove_cv<Tp>::type>::type {};

/* is_member_function_pointer */
namespace internal {
template <typename>
struct is_member_function_pointer : public zstd::false_type {};
template <typename Tp, typename Class>
struct is_member_function_pointer<Tp Class::*> :
  public integral_constant<bool, zstd::is_function<Tp>::value> {};
}  // namespace internal
template <typename Tp>
struct is_member_function_pointer :
  public internal::is_member_function_pointer<
  typename remove_cv<Tp>::type>::type {};

}  // namespace zstd

#endif  // ZSTD_INTERNAL_TYPE_TRAITS_PRIMARY_TYPE_CATEGORY_H_
