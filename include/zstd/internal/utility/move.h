#ifndef ZSTD_INTERNAL_UTILITY_MOVE_H_
#define ZSTD_INTERNAL_UTILITY_MOVE_H_

#include "../type_traits/conditional_type.h"
#include "../type_traits/reference_modifier.h"
#include "../type_traits/type_traits_logic.h"
#include "../type_traits/class_property.h"

namespace zstd {

/* move */
template <typename Tp>
constexpr typename zstd::remove_reference<Tp>::type&& 
move(Tp&& t) noexcept {
  return static_cast<typename zstd::remove_reference<Tp>::type&&>(t);
}


/* move_if_noexcept */
namespace internal {

template <typename Tp>
struct move_if_noexcept_cond : 
  public and_t<not_t<zstd::is_nothrow_move_constructible<Tp>>,
               zstd::is_copy_constructible<Tp>>::type {};

}  // namespace internal

template <typename Tp>
constexpr typename zstd::conditional<
internal::move_if_noexcept_cond<Tp>::value, const Tp&, Tp&&>::type
move_if_noexcept(Tp& x) noexcept {
  return zstd::move(x);
}

}  // namespace zstd

#endif  // ZSTD_INTERNAL_UTILITY_MOVE_H_