#ifndef ZSTD_INTERNAL_VECTOR_VECTOR_H_
#define ZSTD_INTERNAL_VECTOR_VECTOR_H_

#include "../cstddef/cstddef.h"
#include "../iterator/iterator_base.h"
#include "../iterator/iterator_traits.h"
#include "../iterator/iterator_operation.h"
#include "../iterator/iterator_adaptor.h"
#include "../iterator/normal_iterator.h"
#include "../memory/allocator.h"
#include "../memory/allocator_traits.h"
#include "../memory/uninitialized.h"
#include "../type_traits/conditional_type.h"
#include "../type_traits/type_relationship.h"
#include "../utility/move.h"
#include "../utility/forward.h"
#include "../utility/swap.h"
#include "../utility/initializer_list.h"
#include "../algorithm/basic_sequence_modifier.h"


namespace zstd {

namespace internal {

template <typename Tp, typename Allocator>
struct vector_base {
  typedef typename zstd::allocator_traits<Allocator>::template
          rebind_alloc<Tp> Tp_allocator_type;
  typedef typename zstd::allocator_traits<Tp_allocator_type>::pointer pointer;

  struct vector_impl : public Tp_allocator_type {
    vector_impl() : 
      Tp_allocator_type(), begin_(0), end_(0), end_of_storage_(0) {}
    vector_impl(const Tp_allocator_type& alloc) noexcept :
      Tp_allocator_type(alloc), begin_(0), end_(0), end_of_storage_(0) {}
    vector_impl(Tp_allocator_type&& alloc) noexcept :
      Tp_allocator_type(zstd::move(alloc)), 
      begin_(0), end_(0), end_of_storage_(0) {}
    void swap(vector_impl& other) noexcept {
      zstd::swap(begin_, other.begin_);
      zstd::swap(end_, other.end_);
      zstd::swap(end_of_storage_, other.end_of_storage_);
    }
    pointer begin_;
    pointer end_;
    pointer end_of_storage_;    
  };

public:
  typedef Allocator allocator_type;
  typedef zstd::size_t size_type;

  vector_base() : impl_() {}
  vector_base(const allocator_type& alloc) noexcept : impl_(alloc) {}
  vector_base(size_type n) : impl_() {
    create_storage(n);
  }
  vector_base(size_type n, const allocator_type& alloc) : impl_(alloc) {
    create_storage(n);
  }
  vector_base(Tp_allocator_type&& alloc) noexcept : impl_(zstd::move(alloc)) {}
  vector_base(vector_base&& other) noexcept : 
    impl_(zstd::move(other.get_Tp_allocator())) {
    this->swap(other.impl_);
  }
  vector_base(vector_base&& other, const allocator_type& alloc) : 
    impl_(alloc) {
    if (other.get_allocator() == alloc) {
      this->impl_.swap(other.impl_);
    } else {
      create_storage(other.impl_.end_ - other.impl_.begin_);
    }
  }
  ~vector_base() noexcept {
    deallocate(this->impl_.begin_, 
               this->impl_.end_of_storage_ - this->impl_.begin_);
  }

  Tp_allocator_type& get_Tp_allocator() noexcept {
    return *static_cast<Tp_allocator_type*>(&this->impl_);
  }
  const Tp_allocator_type& get_Tp_allocator() const noexcept {
    return *static_cast<const Tp_allocator_type*>(&this->impl_);
  }
  allocator_type get_allocator() const noexcept {
    return allocator_type(get_Tp_allocator());
  }

public:
  pointer allocate(size_type n) {
    if (n == 0) return 0;
    return zstd::allocator_traits<Tp_allocator_type>::allocate(impl_, n);
  }
  void deallocate(pointer p, size_type n) {
    if (p) {
      zstd::allocator_traits<Tp_allocator_type>::deallocate(impl_, p, n);
    }
  }

  vector_impl impl_;

private:
  void create_storage(size_type n) {
    this->impl_.begin_ = this->allocate(n);
    this->impl_.end_ = this->impl_.begin_;
    this->impl_.end_of_storage_ = this->impl_.begin_ + n;
  }
};

}  // namespace internal

template <typename Tp, typename Allocator = zstd::allocator<Tp>>
class vector : protected internal::vector_base<Tp, Allocator> {
  typedef internal::vector_base<Tp, Allocator> Base;
  typedef typename Base::Tp_allocator_type Tp_allocator_type;
  typedef allocator_traits<Tp_allocator_type> Alloc_traits;
public:
  typedef Tp value_type;
  typedef Allocator allocator_type;
  typedef zstd::size_t size_type;
  typedef zstd::ptrdiff_t difference_type;
  typedef typename Allocator::reference reference;
  typedef typename Allocator::const_reference const_reference;
  typedef typename Base::pointer pointer;
  typedef typename Alloc_traits::const_pointer const_pointer;
  typedef internal::normal_iterator<pointer, vector> iterator;
  typedef internal::normal_iterator<const_pointer, vector> const_iterator;
  typedef zstd::reverse_iterator<iterator> reverse_iterator;
  typedef zstd::reverse_iterator<const_iterator> const_reverse_iterator;
  
  vector() noexcept(is_nothrow_default_constructible<Allocator>::value) :
    Base() {}
  explicit vector(const allocator_type& alloc) noexcept : Base(alloc) {}
  explicit vector(size_type n, 
                  const allocator_type& alloc = allocator_type()) :
    Base(n, alloc) {
    default_initialize(n);
  }
  vector(size_type n, const Tp& value, 
         const allocator_type& alloc = allocator_type()) : Base(n, alloc) {
    fill_initialize(n, value);
  }
  template <typename InputIterator>
  vector(InputIterator first, InputIterator last, 
         const allocator_type& alloc = allocator_type()) : Base(alloc) {
    initialize_dispatch(first, last, zstd::false_type());
  }
  vector(initializer_list<Tp> init_list, 
         const allocator_type& alloc = allocator_type()) : Base(alloc) {
    range_initialize(init_list.begin(), init_list.end(), 
                     zstd::random_access_iterator_tag());
  }
         
  vector(const vector& other) : 
    Base(other.size(), Alloc_traits::select_on_container_copy_construction(
         other.get_Tp_allocator())) {
    this->impl_.end_ = zstd::internal::uninitialized_copy_alloc(
      other.begin(), other.end(), get_Tp_allocator());
  }
  vector(const vector& other, const allocator_type& alloc) : 
    Base(other.size(), alloc) {
    this->impl_.end_ = zstd::internal::uninitialized_copy_alloc(
      other.begin(), other.end(), this->impl_.begin_, get_Tp_allocator());
  }
  vector(vector&& other) noexcept : Base(zstd::move(other)) {}
  vector(vector&& other, const allocator_type& alloc) : 
    Base(zstd::move(other), alloc) {
    if (other.get_allocator() != alloc) {
      this->impl_.end_ = zstd::internal::uninitialized_move_alloc(
        other.begin(), other.end(), this->impl_.begin_, get_Tp_allocator());
      other.clear();
    }
  }
  
  vector& operator=(const vector& other) {
    // TODO
  }
  vector& operator=(vector&& other) {
    // TODO
  }
  vector& operator=(initializer_list<Tp> init_list) {
    assign(init_list.begin(), init_list.end());
    return *this;
  }
         
  ~vector() noexcept {
    zstd::internal::destroy(this->impl_.begin_, this->impl_.end_,
      get_Tp_allocator());
  }
  
  void assign(size_type n, const Tp& value) {
    fill_assign(n, value);
  }
  template <typename InputIterator, 
            typename = 
            typename enable_if<is_convertible<
            typename iterator_traits<InputIterator>::iterator_category,
            input_iterator_tag>::value>::type>
  void assign(InputIterator first, InputIterator last) {
    assign_dispatch(first, last, false_type());
  }
  void assign(initializer_list<Tp> init_list) {
    this->assign(init_list.begin(), init_list.end());
  }
  
  allocator_type get_allocator() const noexcept {
    return internal::vector_base<Tp, Tp_allocator_type>::get_allocator();
  }
  
  iterator begin() noexcept {
    return iterator(this->impl_.begin_);
  }
  const_iterator begin() const noexcept {
    return const_iterator(this->impl_.begin_);
  }
  const_iterator cbegin() const noexcept {
    return const_iterator(this->impl_.begin_);
  }
  iterator end() noexcept {
    return iterator(this->impl_.end_);
  }
  const_iterator end() const noexcept {
    return const_iterator(this->impl_.end_);
  }
  const_iterator cend() const noexcept {
    return const_iterator(this->impl_.end_);
  }
  reverse_iterator rbegin() noexcept {
    return reverse_iterator(end());
  }
  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(end());
  }
  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(end());
  }
  reverse_iterator rend() noexcept {
    return reverse_iterator(begin());
  }
  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(begin());
  }
  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(begin());
  }
  
  bool empty() const noexcept { return begin() == end(); }
  size_type size() const noexcept {
    return size_type(this->impl_.end_ - this->impl_.begin_);
  }
  size_type max_size() const noexcept {
    return Alloc_traits::max_size(get_Tp_allocator());
  }
  size_type capacity() const noexcept {
    return size_type(this->impl_.end_of_storage_ - this->impl_.begin_);
  }
  
  void reserve(size_type n) {}
  void shrink_to_fit() noexcept {}
  
  reference operator[](size_type n) noexcept {
    return *(this->impl_.begin_ + n);
  }
  const_reference operator[](size_type n) const noexcept {
    return *(this->impl_.begin_ + n);
  }
  reference at(size_type n) {
    range_check(n);
    return this->operator[](n);
  }
  const_reference at(size_type n) const {
    range_check(n);
    return this->operator[](n);
  }  
  
  reference front() noexcept { return *begin(); }
  const_reference front() const noexcept { return *begin(); }
  reference back() noexcept { return *(end() - 1); }
  const_reference back() const noexcept { return *(end() - 1); }
  
  Tp* data() noexcept {
    return data_ptr(this->impl_.begin_);
  }
  const Tp* data() const noexcept {
    return data_ptr(this->impl_.begin_);
  }
  
  void clear() noexcept {
    erase_at_end(this->impl_.begin_);
  }
  
  iterator insert(const_iterator position, const value_type& value) {
    const size_type n = position - begin();
    if (this->impl_.end_ != this->impl_.end_of_storage_ && position != end()) {
      Alloc_traits::construct(this->impl_, this->impl_.end_, value);
      this->impl_.end_ += 1;
    } else {
      const auto pos = begin() + (position - cbegin());
      if (this->impl_.end_ != this->impl_.end_of_storage_) {
        Tp value_copy = value;
        insert_aux(pos, zstd::move(value_copy));
      } else {
        insert_aux(pos, value);
      }
    }
    return iterator(this->impl_.begin_ + n);
  }
  iterator insert(const_iterator position, value_type&& value) {
    return emplace(position, zstd::move(value));
  }
  iterator insert(const_iterator position, size_type n, 
                  const value_type& value) {
    difference_type offset = position - cbegin();
    fill_insert(begin() + offset, n, value);
    return begin() + offset;
  }
  template <typename InputIterator, 
            typename = typename enable_if<is_convertible<
            typename iterator_traits<InputIterator>::iterator_category,
            input_iterator_tag>::value>::type>
  iterator insert(const_iterator position, InputIterator first, 
                  InputIterator last) {
    difference_type offset = position - cbegin();
    insert_dispatch(begin() + offset, first, last, false_type());
    return begin() + offset;
  }
  iterator insert(const_iterator position, initializer_list<Tp> init_list) {
    this->insert(position, init_list.begin(), init_list.end());
  }
  
  template <typename... Args>
  iterator emplace(const_iterator position, Args&&... args) {
    const size_type offset = position - cbegin();
    if (this->impl_.end_ != this->impl_.end_of_storage_ && position == end()) {
      Alloc_traits::construct(this->impl_, this->impl_.end_,
        zstd::forward<Args>(args)...);
      this->impl_.end_ += 1;
    } else {
      insert_aux(begin() + offset, zstd::forward<Args>(args)...);
    }
    return iterator(this->impl_.begin_ + offset);
  }
  
  iterator erase(const_iterator position) {
    return erase_aux(begin() + (position - cbegin()));
  }
  iterator erase(const_iterator first, const_iterator last) {
    return erase_aux(begin() + (first - cbegin()), 
                     begin() + (last - cbegin()));
  }
  
  void push_back(const value_type& value) {
    if (this->impl_.end_ != this->impl_.end_of_storage_) {
      Alloc_traits::construct(this->impl_, this->impl_.end_, value);
      this->impl_.end_ += 1;
    } else {
      emplace_back_aux(value);
    }
  }
  void push_back(value_type&& value) {
    emplace_back(zstd::move(value));
  }
  template <typename... Args>
  void emplace_back(Args&&... args) {
    if (this->impl_.end_ != this->impl_.end_of_storage_) {
      Alloc_traits::construct(this->impl_, this->impl_.end_,
        zstd::forward<Args>(args)...);
      this->impl_.end_ += 1;
    } else {
      emplace_back_aux(zstd::forward<Args>(args)...);
    }
  }
  void pop_back() noexcept {
    this->impl_.end_ -= 1;
    Alloc_traits::destroy(this->impl_, this->impl_.end_);
  }
  
  void resize(size_type n) {
    if (n > size()) {
      default_append(n - size());
    } else if (n < size()) {
      erase_at_end(this->impl_.begin_ + n);
    }
  }
  void resize(size_type n, const value_type& value) {
    if (n > size()) {
      insert(end(), n - size(), value);
    } else if (n < size()) {
      erase_at_end(this->impl_.begin_ + n);
    }
  }
  
  void swap(vector& other) {
    this->impl_.swap(other.impl_);
    Alloc_traits::swap(get_Tp_allocator(), other.get_Tp_allocator());
  }

protected:
  using Base::allocate;
  using Base::deallocate;
  using Base::get_Tp_allocator;
  using Base::impl_;

  void default_initialize(size_type n) {
    zstd::internal::uninitialized_default_n_alloc(this->impl_.begin_, n, 
      get_Tp_allocator());
    this->impl_.end_ = this->impl_.end_of_storage_;
  }

  void fill_initialize(size_type n, const value_type& value) {
    zstd::internal::uninitialized_fill_n_alloc(this->impl_.begin_, n, value,
      get_Tp_allocator());
    this->impl_.end_ = this->impl_.end_of_storage_;
  }

  template <typename Integer>
  void initialize_dispatch(Integer n, Integer value, zstd::true_type) {
    this->impl_.begin_ = allocate(static_cast<size_type>(n));
    this->impl_.end_of_storage_ = 
      this->impl_.begin_ + static_cast<size_type>(n);
    fill_initialize(static_cast<size_type>(n), value);
  }
  template <typename InputIterator>
  void initialize_dispatch(InputIterator first, InputIterator last, 
                           zstd::false_type) {
    range_initialize(first, last,
      typename zstd::iterator_traits<InputIterator>::iterator_category());
  }

  template <typename InputIterator>
  void range_initialize(InputIterator first, InputIterator last,
                        zstd::input_iterator_tag) {
    for (; first != last; ++first) {
      emplace_back(*first);
    }
  }
  template <typename ForwardIterator>
  void range_initialize(ForwardIterator first, ForwardIterator last,
                        zstd::forward_iterator_tag) {
    const size_type n = zstd::distance(first, last);
    this->impl_.begin_ = this->allocate(n);
    this->impl_.end_of_storage_ = this->impl_.begin_ + n;
    this->impl_.end_ = zstd::internal::uninitialized_copy_alloc(
      first, last, this->impl_.begin_, get_Tp_allocator());
  }

  void fill_assign(size_type n, const value_type& value) {
    if (n > capacity()) {
      vector new_vec(n, value, get_Tp_allocator());
      new_vec.impl_.swap(this->impl_);
    } else if (n > size()) {
      zstd::fill(begin(), end(), value);
      zstd::internal::uninitialized_fill_n_alloc(
        this->impl_.end_, n - size(), value, get_Tp_allocator());
      this->impl_.end_ += n - size();
    } else {
      erase_at_end(zstd::fill_n(this->impl_.begin_, n, value));
    }
  }
  
  // For assign(size_type n, const Tp& value) with Tp = size_type
  template <typename Integer>
  void assign_dispatch(Integer n, Integer value, true_type) {
    fill_assign(n, value);
  }
  // For assign(InputIterator first, InputIterator last)
  template <typename InputIterator>
  void assign_dispatch(InputIterator first, InputIterator last, false_type) {
    assign_aux(first, last, 
               typename iterator_traits<InputIterator>::iterator_category());
  }

  template <typename InputIterator>
  void assign_aux(InputIterator first, InputIterator last, 
                  input_iterator_tag) {
    pointer current(this->impl_.begin_);
    for (; first != last && current != this->impl_.end_; ++current, ++first) {
      *current = *first;
    }
    if (first == last) erase_at_end(current);
    else insert(end(), first, last);
  }
  template <typename ForwardIterator>
  void assign_aux(ForwardIterator first, ForwardIterator last,
                  forward_iterator_tag) {
    const size_type len = zstd::distance(first, last);
    if (len > capacity()) {
      pointer new_begin(allocate_and_copy(len, first, last));
      zstd::internal::destroy(this->impl_.begin_, this->impl_.end_,
        get_Tp_allocator());
      deallocate(this->impl_.begin_,
        this->impl_.end_of_storage_ - this->impl_.begin_);
      this->impl_.begin_ = new_begin;
      this->impl_.end_= this->impl_.begin_ + len;
      this->impl_.end_of_storage_ = this->impl_.end_;
    } else if (len > size()) {
      ForwardIterator mid = first;
      zstd::advance(mid, size());
      zstd::copy(first, mid, this->impl_.begin_);
      this->impl_.end_ = zstd::internal::uninitialized_copy_alloc(
        mid, last, this->impl_.end_, get_Tp_allocator());
    } else {
      erase_at_end(zstd::copy(first, last, this->impl_.begin_));
    }
  }

  void erase_at_end(pointer position) {
    zstd::internal::destroy(position, this->impl_.end_, get_Tp_allocator());
    this->impl_.end_ = position;
  }

  void range_check(size_type n) const {
    if (n >= size()) {
      throw;
    }
  }
  
  void check_len(size_type len, const char* info) const {
    if (max_size() - size() < len) {
      throw;
    }
  }
  size_type get_len(size_type n) {
    const size_type len = (n < size()) ? 2 * size() : size() + n;
    return (len < size() || len > max_size()) ? max_size() : len;
  }

  template <typename Tp1>
  Tp1* data_ptr(Tp1* ptr) const { return ptr; }
  template <typename Pointer>
  typename zstd::pointer_traits<Pointer>::element_type* 
  data_ptr(Pointer ptr) const {
    return empty() ? nullptr : zstd::addressof(*ptr);
  }

  template <typename ForwardIterator>
  pointer allocate_and_copy(size_type n, ForwardIterator first, 
                            ForwardIterator last) {
    pointer result = this->allocate(n);
    try {
      zstd::internal::uninitialized_copy_alloc(
        first, last, result, get_Tp_allocator());
    } catch (...) {
      deallocate(result, n);
      throw;
    }
  }

  void fill_insert(iterator position, size_type n, const value_type& value) {
    if (n == 0) return;
    // Enough space to insert
    if (size_type(this->impl_.end_of_storage_ - this->impl_.end_) >= n) {
      const size_type n_remainder = end() - position;
      value_type value_copy(value);
      pointer old_finish(this->impl_.end_);
      // No need to construct the inserted elems
      if (n_remainder > n) {
        zstd::internal::uninitialized_move_alloc(this->impl_.end_ - n,
          this->impl_.end_, this->impl_.end_, get_Tp_allocator());
        this->impl_.end_ += n;
        zstd::move_backward(position.base(), old_finish - n, old_finish);
        zstd::fill(position.base(), position.base() + n, value_copy);
      } else {
      // Need to construct
        zstd::internal::uninitialized_fill_n_alloc(this->impl_.end_, 
          n - n_remainder, value_copy, get_Tp_allocator());
        this->impl_.end_ += n - n_remainder;
        zstd::internal::uninitialized_move_alloc(position.base(), old_finish, 
          this->impl_.end_, get_Tp_allocator());
        this->impl_.end_ += n_remainder;
        zstd::fill(position.base(), old_finish, value_copy);
      }
    } else {
    // Not enough space
      check_len(n);
      const size_type len = get_len(n);
      const size_type n_before = position - begin();
      pointer new_begin(this->allocate(len));
      pointer new_end(new_begin);
      try {
        zstd::internal::uninitialized_fill_n_alloc(
          new_begin + n_before, n, value, get_Tp_allocator());
        new_end = 0;
        new_end = zstd::internal::uninitialized_move_alloc(
          this->impl_.begin_, position.base(), new_begin, get_Tp_allocator());
        new_end += n;
        new_end = zstd::internal::uninitialized_move_alloc(position.base(), 
          this->impl_.end_, new_end, get_Tp_allocator());
      } catch (...) {
        if (!new_end) {
          zstd::internal::destroy(new_begin + n_before, 
            new_begin + n_before + n, get_Tp_allocator());
        } else {
          zstd::internal::destroy(new_begin, new_end, get_Tp_allocator());
        }
        deallocate(new_begin, len);
        throw;
      }
      zstd::internal::destroy(this->impl_.begin_, this->impl_.end_,
        get_Tp_allocator());
      deallocate(this->impl_.begin_, 
        this->impl_.end_of_storage_ - this.impl_.begin_);
      this->impl_.begin_ = new_begin;
      this->impl_.end_ = new_end;
      this->impl_.end_of_storage_ = new_begin + len;
    }
  }

  template <typename Integer>
  void insert_dispatch(iterator position, Integer n, Integer value, 
                       true_type) {
    fill_insert(position, n, value);
  }
  template <typename InputIterator>
  void insert_dispatch(iterator position, InputIterator first,
                       InputIterator last, false_type) {
    range_insert(position, first, last, 
      typename zstd::iterator_traits<InputIterator>::iterator_category());
  }

  template <typename InputIterator>
  void range_insert(iterator position, InputIterator first, 
                    InputIterator last, input_iterator_tag) {
    for (; first != last; ++first) {
      position = insert(position, *first);
      ++position;
    }
  }
  template <typename ForwardIterator>
  void range_insert(iterator position, ForwardIterator first,
                    ForwardIterator last, forward_iterator_tag) {
    if (first == last) return;
    const size_type len = zstd::distance(first, last);
    // Enough storage for insert
    if (size_type(this->impl_.end_of_storage_ - this->impl_.end_) >= len) {
      const size_type elems_after = end() - position;
      pointer old_end = this->impl_.end_;
      if (elems_after > len) {
      // No need to construct for elems to be inserted
        zstd::internal::uninitialized_move_alloc(this->impl_.end_ - len,
          this->impl_.end_, this->impl_.end_, get_Tp_allocator());
        this->impl_.end_ += len;
        zstd::move_backward(position.base(), old_end - len, old_end);
        zstd::copy(first, last, position);
      } else {
      // Need to construct for elems to be inserted
        ForwardIterator mid = first;
        zstd::advance(mid, elems_after);
        zstd::internal::uninitialized_copy_alloc(mid, last, this->impl_.end_,
          get_Tp_allocator());
        this->impl_.end_ += len - elems_after;
        zstd::internal::uninitialized_move_alloc(position.base(), old_end, 
          this->impl_.end_, get_Tp_allocator());
        this->impl_.end_ += elems_after;
        zstd::copy(first, mid, position);
      }
    } else {
    // Not enough storage
      check_len(len, "");
      size_type new_len = get_len(len);
      pointer new_begin(this->allocate(new_len));
      pointer new_end(new_begin);
      try {
        new_end = zstd::internal::uninitialized_move_if_noexcept_alloc(
          this->impl_.begin_, position.base(), new_begin, get_Tp_allocator());
        new_end = zstd::internal::uninitialized_copy_alloc(first, last, 
          new_end, get_Tp_allocator());
        new_end = zstd::internal::uninitialized_move_if_noexcept_alloc(
          position.base(), this->impl_.end_, new_end, get_Tp_allocator());
      } catch (...) {
        zstd::internal::destroy(new_begin, new_end, get_Tp_allocator());
        deallocate(new_begin, new_len);
        throw;
      }
      zstd::internal::destroy(this->impl_.begin_, this->impl_.end_,
        get_Tp_allocator());
      deallocate(this->impl_.begin_, 
        this->impl_.end_of_storage_ - this->impl_.begin_);
      this->impl_.begin_ = new_begin;
      this->impl_.end_ = new_end;
      this->impl_.end_of_storage_ = new_begin + new_len;
    }
  }

  void default_append(size_type n) {
    if (n == 0) return;
    // Enough space for elems to be appended
    if (size_type(this->impl_.end_of_storage_ - this->impl_.end_) >= n) {
      zstd::internal::uninitialized_default_n_alloc(this->impl_.end_, n, 
        get_Tp_allocator());
      this->impl_.end_ += n;
    } else {
    // Not enough space
      check_len(n, "");
      const size_type len = get_len(n);
      const size_type old_size = size();
      pointer new_begin(this->allocate(len));
      pointer new_end(new_begin);
      try {
        new_end = zstd::internal::uninitialized_move_if_noexcept_alloc(
          this->impl_.begin_, this->impl_.end_, new_begin, get_Tp_allocator());
        zstd::internal::uninitialized_default_n_alloc(new_end, n, 
          get_Tp_allocator());
        new_end += n;
      } catch (...) {
        zstd::internal::destroy(new_begin, new_end, get_Tp_allocator());
        deallocate(new_begin, len);
        throw;
      }
      zstd::internal::destroy(this->impl_.begin_, this->impl_.end_,
        get_Tp_allocator());
      deallocate(this->impl_.begin_, 
        this->impl_.end_of_storage_ - this->impl_.begin_);
      this->impl_.begin_ = new_begin;
      this->impl_.end_ = new_end;
      this->impl_.end_of_storage_ = new_begin + len;
    }
  }

  template <typename... Args>
  void insert_aux(iterator position, Args&&... args) {
    if (this->impl_.end_ != this->impl_.end_of_storage_) {
    // Have space for the new element
      Alloc_traits::construct(this->impl_, this->impl_.end_,
        zstd::move(*(this->impl_.end_ - 1)));
      this->impl_.end_ += 1;
      zstd::move_backward(position.base(), this->impl_.end_ - 2,
                          this->impl_.end_ - 1);
      *position = value_type(zstd::forward<Args>(args)...);
    } else {
    // No space for the new element
      check_len(1, "");
      const size_type len = get_len(1);
      const size_type elems_before = position - begin();
      pointer new_begin(this->allocate(len));
      pointer new_end(new_begin);
      try {
        Alloc_traits::construct(this->impl_, new_begin + elems_before,
          zstd::forward<Args>(args)...);
        new_end = 0;
        new_end = zstd::internal::uninitialized_move_if_noexcept_alloc(
          this->impl_.begin_, position.base(), new_begin, get_Tp_allocator());
        ++new_end;
        new_end = zstd::internal::uninitialized_move_if_noexcept_alloc(
          position.base(), this->impl_.end_, new_end, get_Tp_allocator());
      } catch (...) {
        if (new_end) {
          Alloc_traits::destroy(this->impl_, new_begin + elems_before);
        } else {
          zstd::internal::destroy(new_begin, new_end, get_Tp_allocator());
        }
        deallocate(new_begin, len);
        throw;
      }
      zstd::internal::destroy(this->impl_.begin_, this->impl_.end_,
        get_Tp_allocator());
      deallocate(this->impl_.begin_, 
        this->impl_.end_of_storage_ - this->impl_.begin_);
      this->impl_.begin_ = new_begin;
      this->impl_.end_ = new_end;
      this->impl_.end_of_storage_ = new_begin + len;
    }
  }

  iterator erase_aux(iterator position) {
    if (position + 1 != end()) {
      zstd::move_backward(position + 1, end(), position);
      --(this->impl_.end_);
      Alloc_traits::destroy(this->impl_, this->impl_.end_);
      return position;
    }
  }
  iterator erase_aux(iterator first, iterator last) {
    if (first != last) {
      if (last != end()) {
        zstd::move_backward(last, end(), first);
      }
      erase_at_end(first.base() + (end() - last));
    }
    return first;
  }

  template <typename... Args>
  void emplace_back_aux(Args&&... args) {
    check_len(1, "");
    const size_type len = get_len(1);
    pointer new_begin = this->allocate(len);
    pointer new_end = new_begin;
    try {
      Alloc_traits::construct(this->impl_, new_begin + size(),
        zstd::forward<Args>(args)...);
      new_end = 0;
      new_end = zstd::internal::uninitialized_move_if_noexcept_alloc(
        this->impl_.begin_, this->impl_.end_, new_begin, get_Tp_allocator());
      ++new_end;
    } catch (...) {
      // TODO: the condition here is different from the the GCC version, 
      //       and the GCC version might be wrong. vector.tcc :429
      if (new_end) {
        // Exception from the constrution of the new element
        Alloc_traits::destroy(this->impl_, new_begin + size());
      } else {
        // Exception from the moving part
        zstd::internal::destroy(new_begin, new_end, get_Tp_allocator());
      }
      deallocate(new_begin, len);
      throw;
    }
    zstd::internal::destroy(this->impl_.begin_, this->impl_.end_,
      get_Tp_allocator());
    deallocate(this->impl_.begin_, 
      this->impl_.end_of_storage_ - this->impl_.begin_);
    this->impl_.begin_ = new_begin;
    this->impl_.end_ = new_end;
    this->impl_.end_of_storage_ = new_begin + len;
  }
};

template <typename Tp, typename Allocator>
bool operator==(const vector<Tp, Allocator>& x, 
                const vector<Tp, Allocator>& y) {}
template <typename Tp, typename Allocator>
bool operator<(const vector<Tp, Allocator>& x, 
               const vector<Tp, Allocator>& y) {}
template <typename Tp, typename Allocator>
bool operator!=(const vector<Tp, Allocator>& x, 
                const vector<Tp, Allocator>& y) {
  return !(x == y);
}
template <typename Tp, typename Allocator>
bool operator>(const vector<Tp, Allocator>& x, 
               const vector<Tp, Allocator>& y) {
  return y < x;
}
template <typename Tp, typename Allocator>
bool operator<=(const vector<Tp, Allocator>& x, 
                const vector<Tp, Allocator>& y) {
  return !(y < x);
}
template <typename Tp, typename Allocator>
bool operator>=(const vector<Tp, Allocator>& x, 
                const vector<Tp, Allocator>& y) {
  return !(x < y);
}

template <typename Tp, typename Allocator>
void swap(vector<Tp, Allocator>& x, vector<Tp, Allocator>& y) {
  x.swap(y);
}

}  // namespace zstd

#endif  // ZSTD_INTERNAL_VECTOR_VECTOR_H_