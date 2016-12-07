#ifndef ZSTD_INTERNAL_MEMORY_NEW_ALLOCATOR_H_
#define ZSTD_INTERNAL_MEMORY_NEW_ALLOCATOR_H_

#include "addressof.h"

#include "../cstddef/cstddef.h"
#include "../utility/forward.h"
#include "../type_traits/type_traits_base.h"

namespace zstd {

namespace internal {

/* new_allocator */
template <typename Tp>
class new_allocator {
public:
	typedef zstd::size_t size_type;
	typedef zstd::ptrdiff_t difference_type;
	typedef Tp value_type;
	typedef Tp* pointer;
	typedef const Tp* const_pointer;
	typedef Tp& reference;
	typedef const Tp& const_reference;
	typedef zstd::true_type propagate_on_container_move_assignment;

	template <typename Other>
	struct rebind { typedef new_allocator<Other> other; };

	new_allocator() noexcept {}
	new_allocator(const new_allocator&) noexcept {}
	template <typename Other>
	new_allocator(const new_allocator<Other>&) noexcept {}
	~new_allocator() noexcept {}

	size_type max_size() const noexcept {
		return size_type(-1) / sizeof(value_type);
	}

	pointer address(reference value) const noexcept {
		return zstd::addressof(value);
	}
	const_pointer address(const_reference value) const noexcept {
		return zstd::addressof(value);
	}

	pointer allocate(size_type n, const void* = 0) {
		if (n > this->max_size()) throw;
		return static_cast<Tp*>(::operator new(n * sizeof(value_type)));
	}
	void deallocate(pointer ptr, size_type) {
		::operator delete(ptr);
	}

  template <typename Tp1, typename... Args>
  void construct(Tp1* ptr, Args&&... args) {
  	::new((void*)ptr) Tp1(zstd::forward<Args>(args)...);
  }
  template <typename Tp1>
  void destroy(Tp1* ptr) { ptr->~Tp1(); }
};

template <typename Tp>
inline bool operator==(const new_allocator<Tp>&, const new_allocator<Tp>&) {
	return true;
}
template <typename Tp>
inline bool operator!=(const new_allocator<Tp>&, const new_allocator<Tp>&) {
	return false;
}

}  // namespace internal

}  // namespace zstd

#endif  // ZSTD_INTERNAL_MEMORY_NEW_ALLOCATOR_H_