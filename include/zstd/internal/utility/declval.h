#ifndef ZSTD_INTERNAL_UTILITY_DECLVAL_H_
#define ZSTD_INTERNAL_UTILITY_DECLVAL_H_

// #include "../type_traits/reference_modifier.h"

namespace zstd {

/* declval */
namespace internal {

template <typename Tp>
struct declval_protector {
  static const bool stop = false;
  static typename zstd::add_rvalue_reference<Tp>::type delegate();
};

}  // namespace zstd

template <typename Tp>
inline typename zstd::add_rvalue_reference<Tp>::type declval() noexcept {
  static_assert(internal::declval_protector<Tp>::stop, 
                "declval() must not be used.");
  return internal::declval_protector<Tp>::delegate();
}

}  // namespace zstd

#endif  // ZSTD_INTERNAL_UTILITY_DECLVAL_H_
