#ifndef ZSTD_INTERNAL_TYPE_TRAITS_CLASS_PROPERTY_H_
#define ZSTD_INTERNAL_TYPE_TRAITS_CLASS_PROPERTY_H_

#include "type_traits_base.h"
#include "type_traits_logic.h"
#include "composite_type_category.h"

#include "../utility/declval.h"

#include <type_traits>  // TODO

namespace zstd {

/* is_constructible */
namespace internal {

// template <typename Tp, typename... Args>
// struct is_constructible_impl : public is_nary_constructible<Tp, Args...> {};

// template <typename Tp, typename Arg>
// struct is_constructible_impl : public is_direct_constructible<Tp, Arg> {};

// template <typename Tp>
// struct is_constructible_impl : public is_default_constructible<Tp> {};

}  // namespace internal

// TODO
template <typename Tp, typename... Args>
using is_constructible = std::is_constructible<Tp, Args...>;


/* is_trivially_constructible */

/* is_nothrow_constructible */
// TODO
template <typename Tp, typename... Args>
using is_nothrow_constructible = std::is_nothrow_constructible<Tp, Args...>;



/* is_default_constructible */

/* is_trivially_default_constructible */

/* is_nothrow_default_constructible */
template <typename Tp>
using is_nothrow_default_constructible = 
      std::is_nothrow_default_constructible<Tp>;



/* is_copy_constructible */
namespace internal {

template <typename Tp, bool = is_referenceable<Tp>::value>
struct is_copy_constructible_impl;

template <typename Tp>
struct is_copy_constructible_impl<Tp, false> :
  public zstd::false_type {};

template <typename Tp>
struct is_copy_constructible_impl<Tp, true> :
  public zstd::is_constructible<Tp, const Tp&> {};

}  // namespace internal

template <typename Tp>
struct is_copy_constructible :
  public internal::is_copy_constructible_impl<Tp> {};


/* is_trivially_copy_constructible */


/* is_nothrow_copy_constructible */
namespace internal {

template <typename Tp, bool = is_referenceable<Tp>::value>
struct is_nothrow_copy_constructible_impl;

template <typename Tp>
struct is_nothrow_copy_constructible_impl<Tp, false> :
  public zstd::false_type {};

template <typename Tp>
struct is_nothrow_copy_constructible_impl<Tp, true> :
  public zstd::is_nothrow_constructible<Tp, const Tp&> {};

}  // namespace internal

template <typename Tp>
struct is_nothrow_copy_constructible :
  public internal::is_nothrow_copy_constructible_impl<Tp> {};



/* is_move_constructible */
namespace internal {

template <typename Tp, bool = is_referenceable<Tp>::value>
struct is_move_constructible_impl;

template <typename Tp>
struct is_move_constructible_impl<Tp, false> :
  public zstd::false_type {};

template <typename Tp>
struct is_move_constructible_impl<Tp, true> :
  public zstd::is_constructible<Tp, Tp&&> {};

}  // namespace internal

template <typename Tp>
struct is_move_constructible :
  public internal::is_move_constructible_impl<Tp> {};


/* is_trivially_move_constructible */


/* is_nothrow_move_constructible */
namespace internal {

template <typename Tp, bool = is_referenceable<Tp>::value>
struct is_nothrow_move_constructible_impl;

template <typename Tp>
struct is_nothrow_move_constructible_impl<Tp, false> :
  public zstd::false_type {};

template <typename Tp>
struct is_nothrow_move_constructible_impl<Tp, true> :
  public zstd::is_nothrow_constructible<Tp, Tp&&> {};

}  // namespace internal

template <typename Tp>
struct is_nothrow_move_constructible :
  public internal::is_nothrow_move_constructible_impl<Tp> {};



/* is_assignable */
namespace internal {

template <typename Tp, typename Up>
struct is_assignable_helper {
private:
  template <typename Tp1, typename Up1, 
            typename = decltype(zstd::declval<Tp1>() = zstd::declval<Up1>())>
  static zstd::true_type test(int);
  template <typename, typename>
  static zstd::false_type test(...);

public:
  typedef decltype(test<Tp, Up>(0)) type;
};

}  // namespace internal

template <typename Tp, typename Up>
struct is_assignable : 
  public internal::is_assignable_helper<Tp, Up>::type {};


/* is_trivially_assignable */


/* is_nothrow_assignable */
namespace internal {

template <typename Tp, typename Up>
struct is_nothrow_assignable_impl : 
  public zstd::integral_constant<bool, 
  noexcept(zstd::declval<Tp>() = zstd::declval<Up>())> {};

}  // namespace internal

template <typename Tp, typename Up>
struct is_nothrow_assignable :
  public internal::and_t<is_assignable<Tp, Up>, 
                         internal::is_nothrow_assignable_impl<Tp, Up>> {};


/* is_copy_assignable */
namespace internal {

template <typename Tp, bool = is_referenceable<Tp>::value>
struct is_copy_assignable_impl;

template <typename Tp>
struct is_copy_assignable_impl<Tp, false> : 
  public zstd::false_type {};

template <typename Tp>
struct is_copy_assignable_impl<Tp, true> :
  public zstd::is_assignable<Tp&, const Tp&> {};

}  // namespace internal

template <typename Tp>
struct is_copy_assignable : 
  public internal::is_copy_assignable_impl<Tp> {};


/* is_trivially_copy_assignable */


/* is_nothrow_copy_assignable */
namespace internal {

template <typename Tp, bool = is_referenceable<Tp>::value>
struct is_nothrow_copy_assignable_impl;

template <typename Tp>
struct is_nothrow_copy_assignable_impl<Tp, false> : 
  public zstd::false_type {};

template <typename Tp>
struct is_nothrow_copy_assignable_impl<Tp, true> :
  public zstd::is_nothrow_assignable<Tp&, const Tp&> {};

}  // namespace internal

template <typename Tp>
struct is_nothrow_copy_assignable :
  public internal::is_nothrow_copy_assignable_impl<Tp> {};



/* is_move_assignable */
namespace internal {

template <typename Tp, bool = is_referenceable<Tp>::value>
struct is_move_assignable_impl;

template <typename Tp>
struct is_move_assignable_impl<Tp, false> : 
  public zstd::false_type {};

template <typename Tp>
struct is_move_assignable_impl<Tp, true> :
  public zstd::is_assignable<Tp&, Tp&&> {};

}  // namespace interal

template <typename Tp>
struct is_move_assignable :
  public internal::is_move_assignable_impl<Tp> {};


/* is_trivially_move_assignable */


/* is_nothrow_move_assignable */
namespace internal {

template <typename Tp, bool = is_referenceable<Tp>::value>
struct is_nothrow_move_assignable_impl;

template <typename Tp>
struct is_nothrow_move_assignable_impl<Tp, false> :
  public zstd::false_type {};

template <typename Tp>
struct is_nothrow_move_assignable_impl<Tp, true> :
  public zstd::is_nothrow_assignable<Tp&, Tp&&> {};

}  // namespace internal

template <typename Tp>
struct is_nothrow_move_assignable :
  public internal::is_nothrow_move_assignable_impl<Tp> {};



/* is_destructible */

/* is_trivially_destructible */

/* is_nothrow_destructible */


/* has_virtual_destructor */


}  // namespace zstd

#endif  // ZSTD_INTERNAL_TYPE_TRAITS_CLASS_PROPERTY_H_
