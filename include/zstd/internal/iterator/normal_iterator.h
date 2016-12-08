#ifndef ZSTD_INTERNAL_ITERATOR_NORMAL_ITERATOR_H_
#define ZSTD_INTERNAL_ITERATOR_NORMAL_ITERATOR_H_

#include "iterator_base.h"
#include "iterator_traits.h"

namespace zstd {

namespace internal {

/* normal_iterator */
template <typename Iterator, typename Container>
class normal_iterator {
public:
  typedef Iterator iterator_type;
  typedef typename iterator_traits<Iterator>::iterator_category
          iterator_category;
  typedef typename iterator_traits<Iterator>::value_type value_type;
  typedef typename iterator_traits<Iterator>::difference_type difference_type;
  typedef typename iterator_traits<Iterator>::reference reference;
  typedef typename iterator_traits<Iterator>::pointer pointer;

  normal_iterator() noexcept : current(Iterator()) {}
  explicit normal_iterator(const Iterator& it) noexcept : current(it) {}
  template <typename Iter>
  normal_iterator(const normal_iterator<Iter, Container>& it) noexcept :
    current(it.base()) {}

  const iterator_type& base() const noexcept { return current; }
  reference operator*()  const noexcept { return *current; }
  pointer operator->() const noexcept { return current; }
  normal_iterator& operator++() noexcept {
    ++current;
    return *this;
  }
  normal_iterator operator++(int) noexcept {
    return normal_iterator(current++);
  }
  normal_iterator& operator--() noexcept {
    --current;
    return *this;
  }
  normal_iterator operator--(int) noexcept {
    return normal_iterator(current--);
  }
  normal_iterator& operator+=(difference_type n) noexcept {
    current += n;
    return *this;
  }
  normal_iterator operator+(difference_type n) const noexcept {
    return normal_iterator(current + n);
  }
  normal_iterator& operator-=(difference_type n) noexcept {
    current -= n;
    return *this;
  }
  normal_iterator operator-(difference_type n) const noexcept {
    return normal_iterator(current - n);
  }
  reference operator[](difference_type n) const noexcept {
    return current[n];
  }

protected:
  Iterator current;
};

template <typename Iterator, typename Container>
inline bool operator==(const normal_iterator<Iterator, Container>& x,
                       const normal_iterator<Iterator, Container>& y)
                       noexcept {
  return x.base() == y.base();
}
template <typename Iter1, typename Iter2, typename Container>
inline bool operator==(const normal_iterator<Iter1, Container>& x,
                       const normal_iterator<Iter2, Container>& y) noexcept {
  return x.base() == y.base();
}
template <typename Iterator, typename Container>
inline bool operator<(const normal_iterator<Iterator, Container>& x,
                      const normal_iterator<Iterator, Container>& y) 
                      noexcept {
  return x.base() < y.base();
}
template <typename Iter1, typename Iter2, typename Container>
inline bool operator<(const normal_iterator<Iter1, Container>& x,
                      const normal_iterator<Iter2, Container>& y) noexcept {
  return x.base() < y.base();
}
template <typename Iterator, typename Container>
inline bool operator!=(const normal_iterator<Iterator, Container>& x,
                       const normal_iterator<Iterator, Container>& y) 
                       noexcept {
  return !(x == y);
}
template <typename Iter1, typename Iter2, typename Container>
inline bool operator!=(const normal_iterator<Iter1, Container>& x,
                       const normal_iterator<Iter2, Container>& y) noexcept {
  return !(x == y);
}
template <typename Iterator, typename Container>
inline bool operator>(const normal_iterator<Iterator, Container>& x,
                      const normal_iterator<Iterator, Container>& y) 
                       noexcept {
  return y < x;
}
template <typename Iter1, typename Iter2, typename Container>
inline bool operator>(const normal_iterator<Iter1, Container>& x,
                       const normal_iterator<Iter2, Container>& y) noexcept {
  return y < x;
}
template <typename Iterator, typename Container>
inline bool operator<=(const normal_iterator<Iterator, Container>& x,
                       const normal_iterator<Iterator, Container>& y) 
                       noexcept {
  return !(y < x);
}
template <typename Iter1, typename Iter2, typename Container>
inline bool operator<=(const normal_iterator<Iter1, Container>& x,
                       const normal_iterator<Iter2, Container>& y) noexcept {
  return !(y < x);
}
template <typename Iterator, typename Container>
inline bool operator>=(const normal_iterator<Iterator, Container>& x,
                       const normal_iterator<Iterator, Container>& y) 
                       noexcept {
  return !(x < y);
}
template <typename Iter1, typename Iter2, typename Container>
inline bool operator>=(const normal_iterator<Iter1, Container>& x,
                       const normal_iterator<Iter2, Container>& y) noexcept {
  return !(x < y);
}
template <typename Iterator, typename Container>
inline typename normal_iterator<Iterator, Container>::difference_type
operator-(const normal_iterator<Iterator, Container>& x,
          const normal_iterator<Iterator, Container>& y) noexcept {
  return x.base() - y.base();
}
template <typename Iter1, typename Iter2, typename Container>
inline typename normal_iterator<Iter1, Container>::difference_type
operator-(const normal_iterator<Iter1, Container>& x,
          const normal_iterator<Iter2, Container>& y) noexcept {
  return x.base() - y.base();
}
template <typename Iterator, typename Container>
inline normal_iterator<Iterator, Container> operator+(
  typename normal_iterator<Iterator, Container>::difference_type n,
  const normal_iterator<Iterator, Container>& it) {
  return normal_iterator<Iterator, Container>(it.base() + n);
}

}  // namespace internal

}  // namespace zstd

#endif  // ZSTD_INTERNAL_ITERATOR_NORMAL_ITERATOR_H_
