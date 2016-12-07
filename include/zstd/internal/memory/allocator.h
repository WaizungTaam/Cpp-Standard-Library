#ifndef ZSTD_INTERNAL_MEMORY_ALLOCATOR_H_
#define ZSTD_INTERNAL_MEMORY_ALLOCATOR_H_

#include "new_allocator.h"

#include "../cstddef/cstddef.h"
#include "../type_traits/type_traits_base.h"

namespace zstd {

namespace internal {

template <typename Tp>
using allocator_base = new_allocator<Tp>;

}  // namespace internal

template <typename Tp>
class allocator : public internal::allocator_base<Tp> {
	typedef internal::allocator_base<Tp> Base;
public:
	typedef Tp value_type;
	typedef Tp* pointer;
	typedef const Tp* const_pointer;
	typedef Tp& reference;
	typedef const Tp& const_reference;
	typedef zstd::size_t size_type;
	typedef zstd::ptrdiff_t difference_type;
	typedef zstd::true_type propagate_on_container_move_assignment;

	template <typename Other>
	struct rebind { typedef allocator<Other> other; };

	allocator() throw() {}
	allocator(const allocator& alloc) throw() : Base(alloc) {}
	template <typename Other>
	allocator(const allocator<Other>&) throw() {}
	~allocator() throw() {}
};

template <>
class allocator<void> {
public:
	typedef void value_type;
	typedef void* pointer;
	typedef const void* const_pointer;
	typedef zstd::size_t size_type;
	typedef zstd::ptrdiff_t difference_type;
	typedef zstd::true_type propagate_on_container_move_assignment;

	template <typename Other>
	struct rebind { typedef allocator<Other> other; };
};

template <typename Tp>
inline bool operator==(const allocator<Tp>&, const allocator<Tp>&) {
	return true;
}
template <typename Tp1, typename Tp2>
inline bool operator==(const allocator<Tp1>&, const allocator<Tp2>&) {
	return true;
}
template <typename Tp>
inline bool operator!=(const allocator<Tp>&, const allocator<Tp>&) {
	return false;
}
template <typename Tp1, typename Tp2>
inline bool operator!=(const allocator<Tp1>&, const allocator<Tp2>&) {
	return false;
}

}  // namespace zstd

#endif  // ZSTD_INTERNAL_MEMORY_ALLOCATOR_H_
