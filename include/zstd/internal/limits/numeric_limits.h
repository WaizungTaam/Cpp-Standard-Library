#ifndef ZSTD_INTERNAL_LIMITS_NUMERIC_LIMITS_H_
#define ZSTD_INTERNAL_LIMITS_NUMERIC_LIMITS_H_

namespace zstd {

namespace internal {

struct numeric_limits_base {
  static constexpr bool is_specialized = false;
  static constexpr int digits = 0;
  static constexpr int digits10 = 0;
  static constexpr int max_digits10 = 0;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = false;
  static constexpr bool is_exact = false;
  static constexpr int radix = 0;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  // TODO
  // static constexpr float_denorm_style has_denorm = denorm_absent;
  static constexpr bool has_denorm_loss = false;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = false;
  static constexpr bool is_modulo = false;
  static constexpr bool traps = false;
  static constexpr bool tinyness_before = false;
  // TODO
  // static constexpr float_round_style round_style = round_toward_zero;
};

}  // namespace internal

/* numeric_limits */
template <typename Tp>
struct numeric_limits : public internal::numeric_limits_base {
  static constexpr Tp min() noexcept { return Tp(); }
  static constexpr Tp max() noexcept { return Tp(); }
  static constexpr Tp lowest() noexcept { return Tp(); }
  static constexpr Tp epsilon() noexcept { return Tp(); }
  static constexpr Tp round_error() noexcept { return Tp(); }
  static constexpr Tp infinity() noexcept { return Tp(); }
  static constexpr Tp quiet_NaN() noexcept { return Tp(); }
  static constexpr Tp signaling_NaN() noexcept { return Tp(); }
  static constexpr Tp denorm_min() noexcept { return Tp(); }
};

template <typename Tp>
struct numeric_limits<const Tp> : public numeric_limits<Tp> {};

template <typename Tp>
struct numeric_limits<volatile Tp> : public numeric_limits<Tp> {};

template <typename Tp>
struct numeric_limits<const volatile Tp> : public numeric_limits<Tp> {};


/* numeric_limits<long> */
template <>
struct numeric_limits<long> {
  static constexpr bool is_specialized = true;

  static constexpr long min() noexcept { return - __LONG_MAX__ - 1; }
  static constexpr long max() noexcept { return __LONG_MAX__; }
  static constexpr long lowest() noexcept { return min(); }
  // TODO
};

}  // namespace zstd

#endif  // ZSTD_INTERNAL_LIMITS_NUMERIC_LIMITS_H_
