#ifndef ZSTD_INTERNAL_ITERATOR_ITERATOR_ADAPTOR_H_
#define ZSTD_INTERNAL_ITERATOR_ITERATOR_ADAPTOR_H_

#include "iterator_base.h"
#include "iterator_traits.h"

#include "../type_traits/conditional_type.h"
#include "../utility/move.h"

namespace zstd {

/* back_insert_iterator */
template <typename Container>
class back_insert_iterator : 
  public iterator<output_iterator_tag, void, void, void, void> {
public:
  typedef Container container_type;

  explicit back_insert_iterator(Container& c) : container_(&c) {}

  back_insert_iterator& operator=(
    const typename Container::value_type& value) {
    container_->push_back(value);
    return *this;
  }
  back_insert_iterator& operator*() { return *this; }
  back_insert_iterator& operator++() { return *this; }
  back_insert_iterator& operator++(int) { return *this; }

protected:
  Container* container_;
};

template <typename Container>
back_insert_iterator<Container> back_inserter(Container& c) {
  return back_insert_iterator<Container>(c);
}


/* front_insert_iterator */
template <typename Container>
class front_insert_iterator : 
  public iterator<output_iterator_tag, void, void, void, void> {
public:
  typedef Container container_type;

  explicit front_insert_iterator(Container& c) : container_(&c) {}

  front_insert_iterator& operator=(
    const typename Container::value_type& value) {
    container_->push_front(value);
    return *this;
  }
  front_insert_iterator& operator*() { return *this; }
  front_insert_iterator& operator++() { return *this; }
  front_insert_iterator& operator++(int) { return *this; }

protected:
  Container* container_;
};

template <typename Container>
front_insert_iterator<Container> front_inserter(Container& c) {
  return front_insert_iterator<Container>(c);
}


/* insert_iterator */
template <typename Container>
class insert_iterator : 
  public iterator<output_iterator_tag, void, void, void, void> {
public:
  typedef Container container_type;

  insert_iterator(Container& c, typename Container::iterator i) :
    container_(c), iter_(i) {}

  insert_iterator& operator=(
    const typename Container::value_type& value) {
    iter_ = container_->insert(iter_, value);
    ++iter_;
    return *this;
  }
  insert_iterator& operator*() { return *this; }
  insert_iterator& operator++() { return *this; }
  insert_iterator& operator++(int) { return *this; }

protected:
  Container* container_;
  typename Container::iterator iter_;
};

template <typename Container, typename Iterator>
inline insert_iterator<Container> inserter(Container& c, Iterator i) {
  insert_iterator<Container>(c, Container::iterator(i));
}


/* reverse_iterator */
template <typename Iterator>
class reverse_iterator : 
  public iterator<
  typename iterator_traits<Iterator>::iterator_category,
  typename iterator_traits<Iterator>::value_type,
  typename iterator_traits<Iterator>::difference_type,
  typename iterator_traits<Iterator>::pointer,
  typename iterator_traits<Iterator>::reference> {
public:
  typedef Iterator iterator_type;
  typedef typename iterator_traits<iterator_type>::iterator_category 
          iterator_category;
  typedef typename iterator_traits<iterator_type>::value_type value_type;
  typedef typename iterator_traits<iterator_type>::difference_type
          difference_type;
  typedef typename iterator_traits<iterator_type>::pointer pointer;
  typedef typename iterator_traits<iterator_type>::reference reference;

  reverse_iterator() {}
  explicit reverse_iterator(iterator_type i) : current_(i) {}
  reverse_iterator(const reverse_iterator& i) : current_(i.current_) {}
  template <typename Iter>
  reverse_iterator(const reverse_iterator<Iter>& i) : current_(i.base()) {}

  iterator_type base() const { return current_; }
  reference operator*() const {
    Iterator ret = current_;
    return *--ret;
  }
  pointer operator->() const { return &(operator*()); }
  reverse_iterator& operator++() {
    --current_;
    return *this;
  }
  reverse_iterator operator++(int) {
    reverse_iterator ret = *this;
    --current_;
    return ret;
  }
  reverse_iterator& operator--() {
    ++current_;
    return *this;
  }
  reverse_iterator operator--(int) {
    reverse_iterator ret = *this;
    ++current_;
    return ret;
  }
  reverse_iterator operator+(difference_type n) const {
    return reverse_iterator(current_ - n);
  }
  reverse_iterator& operator+=(difference_type n) {
    current_ -= n;
    return *this;
  }
  reverse_iterator operator-(difference_type n) const {
    return reverse_iterator(current_ + n);
  }
  reverse_iterator& operator-=(difference_type n) {
    current_ += n;
    return *this;
  }
  reference operator[](difference_type n) const {
    return *(*this + n);
  }

protected:
  Iterator current_;
};

template <typename Iterator>
inline bool operator==(const reverse_iterator<Iterator>& x,
                       const reverse_iterator<Iterator>& y) {
  return x.base() == y.base();
}
template <typename Iterator>
inline bool operator<(const reverse_iterator<Iterator>& x,
                      const reverse_iterator<Iterator>& y) {
  return y.base() < x.base();
}
template <typename Iterator>
inline bool operator!=(const reverse_iterator<Iterator>& x,
                       const reverse_iterator<Iterator>& y) {
  return !(x == y);
}
template <typename Iterator>
inline bool operator>(const reverse_iterator<Iterator>& x,
                      const reverse_iterator<Iterator>& y) {
  return y < x;
}
template <typename Iterator>
inline bool operator<=(const reverse_iterator<Iterator>& x,
                       const reverse_iterator<Iterator>& y) {
  return !(y < x);
}
template <typename Iterator>
inline bool operator>=(const reverse_iterator<Iterator>& x,
                       const reverse_iterator<Iterator>& y) {
  return !(x < y);
}
template <typename Iterator>
inline typename reverse_iterator<Iterator>::difference_type operator-(
  const reverse_iterator<Iterator>& x, 
  const reverse_iterator<Iterator>& y) {
  return y.base() - x.base();
}
template <typename Iterator>
inline reverse_iterator<Iterator> operator+(
  typename reverse_iterator<Iterator>::difference_type n,
  const reverse_iterator<Iterator>& i) {
  return reverse_iterator<Iterator>(i.base() - n);
}

template <typename Iterator>
inline reverse_iterator<Iterator> make_reverse_iterator(Iterator i) {
  return reverse_iterator<Iterator>(i);
}


/* move_iterator */
template <typename Iterator>
class move_iterator {
public:
  typedef Iterator iterator_type;
  typedef typename iterator_traits<Iterator>::iterator_category 
          iterator_category;
  typedef typename iterator_traits<Iterator>::value_type value_type;
  typedef typename iterator_traits<Iterator>::difference_type difference_type;
  typedef Iterator pointer;
  typedef value_type&& reference;

  move_iterator() {}
  explicit move_iterator(iterator_type i) : current_(i) {}
  template <typename Iter>
  move_iterator(const move_iterator<Iter>& i) : current_(i.base()) {}

  iterator_type base() const { return current_; }
  reference operator*() const { return move(*current_); }
  pointer operator->() const { return current_; }
  move_iterator& operator++() {
    ++current_;
    return *this;
  }
  move_iterator operator++(int) {
    move_iterator ret = *this;
    ++current_;
    return ret;
  }
  move_iterator& operator--() {
    --current_;
    return *this;
  }
  move_iterator operator--(int) {
    move_iterator ret = *this;
    --current_;
    return ret;
  }
  move_iterator operator+(difference_type n) const {
    return move_iterator(current_ + n);
  }
  move_iterator& operator+=(difference_type n) {
    current_ += n;
    return *this;
  }
  move_iterator operator-(difference_type n) const {
    return move_iterator(current_ - n);
  }
  move_iterator& operator-=(difference_type n) {
    current_ -= n;
    return *this;
  }
  reference operator[](difference_type n) const {
    return move(current_[n]);
  }

protected:
  Iterator current_;
};

template <typename Iterator>
inline bool operator==(const move_iterator<Iterator>& x, 
                       const move_iterator<Iterator>& y) {
  return x.base() == y.base();
}
template <typename Iterator>
inline bool operator<(const move_iterator<Iterator>& x,
                      const move_iterator<Iterator>& y) {
  return x.base() < y.base();
}
template <typename Iterator>
inline bool operator!=(const move_iterator<Iterator>& x, 
                       const move_iterator<Iterator>& y) {
  return !(x == y);
}
template <typename Iterator>
inline bool operator>(const move_iterator<Iterator>& x,
                      const move_iterator<Iterator>& y) {
  return y < x;
}
template <typename Iterator>
inline bool operator<=(const move_iterator<Iterator>& x, 
                       const move_iterator<Iterator>& y) {
  return !(y < x);
}
template <typename Iterator>
inline bool operator>=(const move_iterator<Iterator>& x, 
                       const move_iterator<Iterator>& y) {
  return !(x < y);
}
template <typename Iterator>
inline typename move_iterator<Iterator>::difference_type operator-(
  const move_iterator<Iterator>& x, 
  const move_iterator<Iterator>& y) {
  return x.base() - y.base();
}
template <typename Iterator>
inline move_iterator<Iterator> operator+(
  typename move_iterator<Iterator>::difference_type n,
  const move_iterator<Iterator>& i) {
  return i + n;
}
template <typename Iterator>
inline move_iterator<Iterator> make_move_iterator(Iterator i) {
  return move_iterator<Iterator>(i);
}

namespace internal {

/* make_move_if_noexcept_iterator */
template <typename Iterator, 
          typename ReturnTp = typename zstd::conditional<
          move_if_noexcept_cond<
          typename zstd::iterator_traits<Iterator>::value_type>::value,
          Iterator, 
          move_iterator<Iterator>>::type>
inline ReturnTp make_move_if_noexcept_iterator(Iterator it) {
  return ReturnTp(it);
}

}  // namespace internal

}  // namespace zstd

#endif  // ZSTD_INTERNAL_ITERATOR_ITERATOR_ADAPTOR_H_