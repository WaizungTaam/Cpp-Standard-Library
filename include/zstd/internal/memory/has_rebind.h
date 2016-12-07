#ifndef ZSTD_INTERNAL_MEMORY_HAS_REBIND_H_
#define ZSTD_INTERNAL_MEMORY_HAS_REBIND_H_

#include "../type_traits/type_traits_base.h"

namespace zstd {
namespace internal {

template <typename Tp, typename Up>
struct has_rebind_helper {
private:
  template <typename Tp1, typename Up1>
  static zstd::true_type test(typename Tp1::template rebind<Up1>*);
  template <typename, typename>
  static zstd::false_type test(...);

public:
  typedef decltype(test<Tp, Up>(0)) type;
};

template <typename Tp, typename Up>
struct has_rebind : public has_rebind_helper<Tp, Up>::type {};

}  // namespace internal
}  // namespace zstd

#endif  // ZSTD_INTERNAL_MEMORY_HAS_REBIND_H_
