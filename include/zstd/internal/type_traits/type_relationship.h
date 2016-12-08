#ifndef ZSTD_INTERNAL_TYPE_TRAITS_TYPE_RELATIONSHIP_H_
#define ZSTD_INTERNAL_TYPE_TRAITS_TYPE_RELATIONSHIP_H_

#include "type_traits_base.h"
#include "primary_type_category.h"

#include "../utility/declval.h"

namespace zstd {

/* is_same */
template <typename, typename>
struct is_same : public false_type {};
template <typename Tp>
struct is_same<Tp, Tp> : public true_type {};

/* is_base_of */
// __is_base_of is a gcc function.
template <typename Base, typename Derived>
struct is_base_of : 
  public integral_constant<bool, __is_base_of(Base, Derived)> {};

/* is_convertible */
namespace internal {
template <typename From, typename To, 
          bool = internal::or_t<
          zstd::is_void<From>, 
          zstd::is_function<To>, 
          zstd::is_array<To>>::value>
struct is_convertible { typedef typename zstd::is_void<To>::type type; };

template <typename From, typename To>
struct is_convertible<From, To, false> {
private:
  template <typename To1>
  static void test_aux(To1);

  template <typename From1, typename To1,
            typename = decltype(test_aux<To1>(zstd::declval<From1>()))>
  static zstd::true_type test(int);

  template <typename, typename>
  static zstd::false_type test(...);

public:
  typedef decltype(test<From, To>(0)) type;
};
}  // namespace internal
template <typename From, typename To>
struct is_convertible : public internal::is_convertible<From, To>::type {};

}  // namespace zstd

#endif  // ZSTD_INTERNAL_TYPE_TRAITS_TYPE_RELATIONSHIP_H_
