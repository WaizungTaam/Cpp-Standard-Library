#ifndef ZSTD_INTERNAL_UTILITY_SWAP_H_
#define ZSTD_INTERNAL_UTILITY_SWAP_H_

namespace zstd {

/* swap */
template <typename Tp>
inline void swap(Tp& a, Tp& b) {
  Tp a_copy = a;
  a = b;
  b = a_copy;
}
template <typename Tp, size_t N>
inline void swap(Tp (&a)[N], Tp (&b)[N]) {
  for (size_t i = 0; i < N; ++i) {
    swap(a[i], b[i]);
  }
}

}  // namespace zstd

#endif  // ZSTD_INTERNAL_UTILITY_SWAP_H_