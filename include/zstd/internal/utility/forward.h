#ifndef ZSTD_INTERNAL_UTILITY_FORWARD_H_
#define ZSTD_INTERNAL_UTILITY_FORWARD_H_

#include "../type_traits/reference_modifier.h"
#include "../type_traits/primary_type_category.h"

namespace zstd {

/* forward */
template <typename Tp>
constexpr Tp&& 
forward(typename zstd::remove_reference<Tp>::type& t) noexcept {
  return static_cast<Tp&&>(t);
}
template <typename Tp>
constexpr Tp&& 
forward(typename zstd::remove_reference<Tp>::type&& t) noexcept {
  static_assert(!zstd::is_lvalue_reference<Tp>::value, 
    "template argument substituting Tp is an lvalue reference type");
  return static_cast<Tp&&>(t);
}

}  // namespace zstd

#endif  // ZSTD_INTERNAL_UTILITY_FORWARD_H_
