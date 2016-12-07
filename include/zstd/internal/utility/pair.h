#ifndef ZSTD_INTERNAL_UTILITY_PAIR_H_
#define ZSTD_INTERNAL_UTILITY_PAIR_H_

namespace zstd {

/* Note: Old Version */
template <typename Tp1, typename Tp2>
struct pair {
  typedef Tp1 first_type;
  typedef Tp2 second_type;

  Tp1 first;
  Tp2 second;

  pair() : first(Tp1()), second(Tp2()) {}
  pair(const Tp1& x, const Tp2& y) : first(x), second(y) {}
  template <typename U1, typename U2>
  pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}
  pair& operator=(const pair& p) {
    first = p.first;
    second = p.second;
    return *this;
  }
  template <typename U1, typename U2>
  pair& operator=(const pair<U1, U2>& p) {
    first = p.first;
    second = p.second;
    return *this;
  }
};

template <typename Tp1, typename Tp2>
inline bool operator==(const pair<Tp1, Tp2>& x, const pair<Tp1, Tp2>& y) {
  return x.first == y.first && x.second == y.second;
}
template <typename Tp1, typename Tp2>
inline bool operator<(const pair<Tp1, Tp2>& x, const pair<Tp1, Tp2>& y) {
  return x.first < y.first ||
         (!(y.first < x.first) && x.second < y.second);
}
template <typename Tp1, typename Tp2>
inline bool operator!=(const pair<Tp1, Tp2>& x, const pair<Tp1, Tp2>& y) {
  return !(x == y);
}
template <typename Tp1, typename Tp2>
inline bool operator>(const pair<Tp1, Tp2>& x, const pair<Tp1, Tp2>& y) {
  return y < x;
}
template <typename Tp1, typename Tp2>
inline bool operator<=(const pair<Tp1, Tp2>& x, const pair<Tp1, Tp2>& y) {
  return !(y < x);
}
template <typename Tp1, typename Tp2>
inline bool operator>=(const pair<Tp1, Tp2>& x, const pair<Tp1, Tp2>& y) {
  return !(x < y);
}

template <typename Tp1, typename Tp2>
inline pair<Tp1, Tp2> make_pair(const Tp1& x, const Tp2& y) {
  return pair<Tp1, Tp2>(x, y);
}

}  // namespace zstd

#endif  // ZSTD_INTERNAL_UTILITY_PAIR_H_
