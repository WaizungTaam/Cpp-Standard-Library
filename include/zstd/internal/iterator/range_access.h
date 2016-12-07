#ifndef ZSTD_INTERNAL_ITERATOR_RANGE_ACCESS_H_
#define ZSTD_INTERNAL_ITERATOR_RANGE_ACCESS_H_

namespace zstd {

template <typename Container>
inline auto begin(Container& c) -> decltype(c.begin()) {
  return c.begin();
}
template <typename Container>
inline auto begin(const Container& c) -> decltype(c.begin()) {
  return c.begin();
}
template <typename Tp, zstd::size_t N>
inline Tp* begin(Tp (&arr)[N]) {
  return arr;
}

template <typename Container>
inline auto end(Container& c) -> decltype(c.end()) {
  return c.end();
}
template <typename Container>
inline auto end(const Container& c) -> decltype(c.end()) {
  return c.end();
}
template <typename Tp, zstd::size_t N>
inline Tp* end(Tp (&arr)[N]) {
  return arr + N;
}

}  // namespace zstd

#endif  // ZSTD_INTERNAL_ITERATOR_RANGE_ACCESS_H_