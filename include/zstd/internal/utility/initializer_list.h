/* 2016-11-15 */
#ifndef ZTSD_INTERNAL_UTILITY_INITIALIZER_LIST
#define ZTSD_INTERNAL_UTILITY_INITIALIZER_LIST

#include "../cstddef/cstddef.h"
#include "../iterator/iterator_adaptor.h"
#include "../utility/initializer_list.h"

namespace zstd {

template <typename Tp>
class initializer_list {
public:
  typedef Tp value_type;
  typedef const Tp& reference;
  typedef const Tp& const_reference;
  typedef zstd::size_t size_type;
  typedef const Tp* iterator;
  typedef const Tp* const_iterator;

  constexpr initializer_list() noexcept : array_(0), len_(0) {}
  constexpr size_type size() const noexcept { return len_; }
  constexpr const_iterator begin() const noexcept { return array_; }
  constexpr const_iterator end() const noexcept { return begin() + size(); }

private:
  constexpr initializer_list(const_iterator array, size_type len) :
    array_(array), len_(len) {}

  iterator array_;
  size_type len_;
};

template <typename Tp>
constexpr typename initializer_list<Tp>::const_iterator 
begin(initializer_list<Tp> il) noexcept {
  return il.begin();
}
template <typename Tp>
constexpr typename initializer_list<Tp>::const_iterator 
end(initializer_list<Tp> il) noexcept {
  return il.end();
}
template <typename Tp>
constexpr reverse_iterator<typename initializer_list<Tp>::const_iterator>
rbegin(initializer_list<Tp> il) noexcept {
  return reverse_iterator<typename initializer_list<Tp>::const_iterator>(
         il.end());
}
template <typename Tp>
constexpr reverse_iterator<typename initializer_list<Tp>::const_iterator>
rend(initializer_list<Tp> il) noexcept {
  return reverse_iterator<typename initializer_list<Tp>::const_iterator>(
         il.begin());
}

}  // namespace zstd

#endif  // ZTSD_INTERNAL_UTILITY_INITIALIZER_LIST