#ifndef ZSTD_INTERNAL_TYPE_TRAITS_TYPE_TRAITS_BASE_H_
#define ZSTD_INTERNAL_TYPE_TRAITS_TYPE_TRAITS_BASE_H_

namespace zstd {

template <typename Tp, Tp val>
struct integral_constant {
  static constexpr Tp value = val;
  typedef Tp value_type;
  typedef integral_constant<Tp, val> type;
  constexpr operator value_type() const { return value; }
  constexpr value_type operator()() const { return value; }
};
template <typename Tp, Tp val>
constexpr Tp integral_constant<Tp, val>::value;


typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;

}  // namespace zstd

#endif  // ZSTD_INTERNAL_TYPE_TRAITS_TYPE_TRAITS_BASE_H_